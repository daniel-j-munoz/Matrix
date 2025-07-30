#include <opencv2/opencv.hpp>
#include "Libraries/Image.h"
#include "Libraries/Matrix.h"
#include <iostream>

using namespace std;
using namespace cv;

VideoWriter video_writer(string path, double fps, int m, int n){
    int fourcc = VideoWriter::fourcc('M', 'P', '4', 'V');
    return VideoWriter(path, fourcc, fps, Size(m, n), false);
}




int main(){
    int width = 101; 
    int height = 101; 
    int center_x = width / 2;
    int center_y = height / 2;


    VideoWriter video = video_writer("diffusion.mp4", 30.0, width, height);


    // Initial Distribution
    Matrix init_dis(width, height); 
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            float arg = -pow(x - center_x, 2) - pow(y - center_y, 2);
            float sigma = 200.0f;
            float value = exp(arg / sigma);
            init_dis.set(x, y, value);
        }
    }


    init_dis.range(0.0f, 255.0f);



    float D = 500.0f; // Diffusion Rate
    for(float t = 0.03333; t < 5; t += 0.03333){
        cout << to_string(t) << "\n";

        float value = 4.0f * D * t; 
        float factor = 1.0f / (value * M_PI);

        // Horizontal Kernel
        Matrix u(1, width);
        for(int x = 0; x < width; x++){
            u.set(
                0, x, 
                sqrt(factor) * exp(-pow(x - center_x, 2) / value)
            ); 
        }

        // Vertical Kernel
        Matrix v(height, 1); 
        for(int y = 0; y < height; y++){
            v.set(
                y, 0, 
                sqrt(factor) * exp(-pow(y - center_y, 2) / value)
            ); 
        }


        // Convolve 
        Matrix thing = init_dis;  
        thing.convolve_sep(u, v);        

        video.write(thing.to_mat());
        
    }

    video.release();

    
    return 0;
}





// VideoWriter vw 
// Mat mat
// vw.write(mat)
// vw.release();



// imagine going beyond this
// and imagine like diffusion models and
// perhaps other applications. and other ways it could be applied and stuff.