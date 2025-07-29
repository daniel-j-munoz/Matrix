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
    int width = 100; 
    int height = 100; 
    Matrix init(width, height);
    
    // Initialize Boundary Condition
    float std = width / 5.0f;
    for(int m = 0; m < init.M; m++){
        int center = init.M / 2;
        float x = (m - center) / std;
        float y = 255 * exp(-pow(x, 2));
        init.set(m, 0, y);
        init.set(m, init.N - 1, y);
    }
    
    for(int n = 0; n < init.N; n++){
        int center = init.N / 2;
        float x = (n - center) / std;
        float y = 255 * exp(-pow(x, 2));
        init.set(0, n, y);
        init.set(init.M - 1, n, y);
    }
    
    vector<float> data = {
        0.0f, 0.25f, 0.0f,
        0.25f, 0.0f, 0.25f,
        0.0f, 0.25f, 0.0f
    };
    Matrix kernel(3, 3, data);
    
    // Set up video writer
    VideoWriter video = video_writer("jacobi_method_evolution.mp4", 30.0, width, height);
    
    // Jacobi Iteration
    for(int nth = 0; nth <= 2500; nth++){
        if(nth % 15 == 0){
            video.write(init.to_mat());
        }
        init.convolve_me(kernel, false);
    }
    
    video.release();
    
    return 0;
}