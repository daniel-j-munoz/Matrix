#include "Image.h"

#include <fstream>


// coefficents argument for rgb? 
Matrix Image::gray_scale(vector<Matrix*> channels){
    Matrix output = Matrix(channels[0]->M, channels[0]->N, 0.0f);
    for(int ith = 0; ith < 3; ith++){
        Matrix channel = *channels[ith];

        float factor = 0.0f; 
        switch(ith){
            case 0: 
                factor = 0.114f;  
                break; 
            case 1: 
                factor = 0.587f;  
                break; 
            case 2: 
                factor = 0.299f;  
                break;
            default: 
                break; 
        }
        channel.scale(factor);
        output = output + channel;
    }

    return output; 
}

bool Image::valid_path(string path){    
    ifstream file(path);
    return file.good();

}


// goes BGR ? 0, 1, 2?
vector<Matrix*> Image::get_channels(string& path){
    Mat image = imread(path);
    image.convertTo(image, CV_32F);
    Mat opencv_channels[3];
    split(image, opencv_channels);
    vector<Matrix*> channels = {}; 
    for(int ith = 0; ith < 3; ith++){
        Mat flat = opencv_channels[ith].reshape(1, opencv_channels[ith].total()); 
        vector<float> data(flat.begin<float>(), flat.end<float>()); 
        channels.push_back(new Matrix(image.rows, image.cols, data));
    }
    return channels; 
}

Matrix Image::get_grayscale_channel(string& path){
    Mat image = imread(path, IMREAD_UNCHANGED);
    image.convertTo(image, CV_32F);
    Mat flat = image.reshape(1, image.total());
    vector<float> data(flat.begin<float>(), flat.end<float>());
    return Matrix(image.rows, image.cols, data);
}



Mat Image::merge_channels(vector<Matrix*>& channels){
    // Matrix -> cv::Mat
    Mat opencv_channels[3];
    for (int ith = 0; ith < 3; ith++) {
        opencv_channels[ith] = channels[ith]->to_mat();
    }
    Mat image;
    merge(opencv_channels, 3, image);
    return image;
}


/**
 * @param size Reduces the quality of image and template to increase speed of conovlution. at the expense of a less accurate answer. 10 is usually a good size
 */
vector<int> Image::find_template(Matrix image, Matrix temp, int value){
    // Mean pooling
    image.resize(near_mult(image.M, value), near_mult(image.N, value));
    image.mean_pool(value); 
    temp.resize(near_mult(temp.M, value), near_mult(temp.N, value));
    temp.mean_pool(value);

    // Resize to odd sized kernel. same width and height
    int size = min(temp.M, temp.N); 
    size = (size % 2 == 0) ? size - 1: size; 
    temp.resize(size, size);

    // Standardized. I don't know why this part works. but it is working.
    // zreo mean then unit std? order matters?
    image.zero_mean();
    image.unit_std();
    temp.zero_mean(); 
    temp.unit_std();

    // Correlate
    image.convolve(temp, true);
    image.range(0, 255.0f);



    // here's the thing though. i don't think you have to explicity reexpand the pixels. 
    // instead i belive you could probalby map the max index from the smaller image to the orignal image 
    // using their sizes. so all you have to do is map their indicies i belive 
    // and i belive one pixel actually might map to a block of pixels. 
    // but you don't have to explcity expand the pxiels 
    image = image.expand_pixels(value);
    return image.index_of_max();  
}





// for color iamges? and grayscale? 
// represent magnitude of graident w/ opacity?
/**
 * @param space spacing between gradients 
 * @param length length of gradients
 */
void Image::display_gradients(Matrix* image, int space, int length){
    image->guassian_blur(9, 2.0f);
    Matrix f_x = image->copy();
    Matrix f_y = image->copy();
    f_x.sep_conv_sobel_x();  // horizontal gradients
    f_y.sep_conv_sobel_y();  // vertical gradients
    
    for(int m = 0; m < image->M; m += space){
        for(int n = 0; n < image->N; n += space){
            float dx = f_x.get(m, n);  
            float dy = f_y.get(m, n);  
            float mag = sqrt(pow(dx, 2.0f) + pow(dy, 2.0f));
            
            if(mag < 0.001f) continue;  
            
            // Normalize
            dx /= mag;
            dy /= mag;
            
            for(int ith = -length; ith <= length; ith++){
                int new_m = floor(m + (dy * ith));  
                int new_n = floor(n + (dx * ith));  
                if(new_m >= 0 && new_m < image->M && new_n >= 0 && new_n < image->N) {
                    image->set(new_m, new_n, 0.0f);
                }
            }
        }
    }
}




// put these methods somewhre else?? ..................................
/**
 * near mult to left 
 */
int Image::near_mult(int value, int n){
    return (value / n) * n; 
    // return((value / n) + 1) * n;  // to the right?
}

int Image::near_pow(int value, int base){
    double kth = log(value) / log(base); 
    kth = floor(kth); // + 1 gives to right? or even ceil? 
    return (int) pow(base, kth);

    // compute closet power of base to left and right 
    // the measure the difference from those to the original value 
    // and then take the one that essentially has the smallest differecne. can do the same for the near mult method?
}

