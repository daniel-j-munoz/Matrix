#include "Data.h"


void Data::absolute(Matrix* A){
    for(int i = 0; i < A->data.size(); i++){
        A->data[i] = abs(A->data[i]);
    }
}

void Data::power(float n, Matrix* A){
    for(int ith = 0; ith < A->data.size(); ith++){
        A->data[ith] = pow(A->data[ith], n);
    }
}

float Data::sum(Matrix A){
    float total = 0.0f; 
    for(float value : A.data){
        total += value; 
    }
    return total;
}




/**
 * @returns {max, row, col}
 */
vector<float> Data::max(Matrix A){
    int row = -1; 
    int col = -1; 
    float max = numeric_limits<float>::lowest();

    for(int m = 0; m < A.M; m++){
        for(int n = 0; n < A.N; n++){
            float value = A.get(m, n); 
            if(value > max){
                max = value; 
                row = m; 
                col = n; 
            }
        }
    }

    return {max, (float)row, (float)col}; 
}

/**
 * @returns {min, row, col}
 */
vector<float> Data::min(Matrix A){
    int row = -1; 
    int col = -1; 
    float min = numeric_limits<float>::max();

    for(int m = 0; m < A.M; m++){
        for(int n = 0; n < A.N; n++){
            float value = A.get(m, n); 
            if(value < min){
                min = value; 
                row = m; 
                col = n; 
            }
        }
    }

    return {min, (float)row, (float)col}; 
}

int Data::nn(float x, Matrix A){
    float min = std::numeric_limits<float>::max();
    int index = -1;
    for(int i = 0; i < A.data.size(); i++){
        if(x - A.data[i] < min){
            min = x - A.data[i];
            index = i;
        }
    }
    return index;
}





// Unitizing & Zeroing


void Data::unit_L2(Matrix *A){
    unit_L(2, A);
}

void Data::unit_L(float p, Matrix *A){
    A->scale(1.0f / A->L(p));
}






void Data::range(float a, float b, Matrix* A){
    float min = Data::min(*A)[0];
    float max = Data::max(*A)[0];
    range(min, max, a, b, A);
}

void Data::range(float a, float b, float c, float d, Matrix* A){
    if (b == a) {
        return;
    } else {
        float factor = (d - c) / (b - a); 
        vector<float> new_data; 
        for(int ith = 0; ith < A->data.size(); ith++){
            A->data[ith] = factor * (A->data[ith] - a) + c;
        }
    }    
}









// // if u add an inverted image w/ it's univernted image, im pretty sure it would go to a constant value or something. maybe even zero
// void Data::invert(){
//     int a = min(); 
//     int b = max(); 
//     scale(-1.0f); 
//     range(a, b);
// }

// row sum, col sum? .....


// float Data::mean(){
//     float sum = 0.0f; 
//     for(float value : data){
//         sum += value; 
//     }
//     return sum / data.size(); 
// }


// float Data::std(){
//     float mu = mean(); 
//     float sum = 0.0f; 
//     for(float value : data){
//         sum += pow(value - mu, 2.0f);
//     }
//     sum /= data.size(); // Variance
//     return sqrt(sum);
// }








// // add distributions and stuff?....




// // freq method?....
// // mode... etc?....
// // interseting.....


// /** @param k if >= k -> 1 */
// void Data::threshold(float k){
//     for(int ith = 0; ith < data.size(); ith++){
//         if(data[ith] >= k){
//             data[ith] = 1.0f;
//         } else {
//             data[ith] = 0.0f;
//         }
//     }
// }

// void Data::randomize(float a, float b){
//     random_device rd;
//     mt19937 gen(rd());
//     uniform_real_distribution<double> dis(a, b);
//     for(int i = 0; i < data.size(); i++){
//         data[i] = dis(gen); 
//     }
// }





// // every number can only be a multiple of the step size basically?

// // by changing the step size to something larger perhaps we could simplfy the data & find more repeating values? 
// // and allow for more compression? essentially it can make the image easier to work w/ data wise bassically
// // imagine having to store 255 differnt values. to just 25 differnt values and still perserve a decent amount of information

// // i guess its like integer multiplpes of the step size?.... im not sure to be honest...
// // very useful function though......
// void Matrix::step_change(float step){
//     // so right now the step size can be really small e..g 5.0 -> 5.00001 
//     // but what if you could change the step size to larger values 
//     // e.g. 5 -> 6.  step size 1 
//     // or even 5 -> 8. step size 3 
//     // this could simplfy the amount of data that you have. and also 
//     // it could create more repeated regions which can then be exploited w/ things like convolution. and perhaps compressing regeions? 
    

//     for(int ith = 0; ith < data.size(); ith++){

//         // the round part is basically finding the nearest integer multiple of the step size basically
//         // choose ceil or floor instead. does always using ceil give a more interesting result?
//         data[ith] = round(data[ith] / step) * step; 
//     }
// }



// void Data::sort(){
//     // implmeent differnt sorting algos later?
//     std::sort(data.begin(), data.end());
// }




// void Data::zero_mean(){
//     // store mean in feild to avoid recomputation?
//     float mu = mean();
//     for(int ith = 0; ith < data.size(); ith++){
//         data[ith] -= mu; 
//     }
// }

// // does this make the std one?
// void Data::unit_std(){
//     float sigma = std(); 
//     for(int ith = 0; ith < data.size(); ith++){
//         data[ith] /= sigma; 
//     }
// }




// // this has some copmutatianly efficent things if im not mistaken
// void Data::zero_mean_unit_std(){
//     float mean_val = 0.0f;
//     float sum_sq = 0.0f;

//     for(float val : data){
//         mean_val += val;
//         sum_sq += val * val;
//     }

//     mean_val /= data.size();
//     float variance = sum_sq / data.size() - mean_val * mean_val;
//     float stddev = sqrt(variance);

//     if(stddev < 1e-6){
//         stddev = 1.0f; // avoid division by zero, treat as flat image
//     }

//     for(float& val : data){
//         val = (val - mean_val) / stddev;
//     }
// }




// void Data::unit_sum(){
//     scale(1.0f / sum());
// }




// // unit_sum, unit_length, unit_mean etc. i think are good names for waht they do. 
// // zero_mean? unit_std? 
// // depending if it zeros or makes the quanityt a unit.









Matrix Data::to_matrix(vector<float> data){
    return Matrix(data.size(), 1, data);
}


Matrix Data::swap(Matrix A, vector<float> swap){
    vector<float> output(A.data.size());
    for(int i = 0; i < output.size(); i++){
        output[i] = A.data[swap[i]];
    }
    return Matrix(output.size(), 1, output);
}