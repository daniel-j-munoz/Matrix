#include <opencv2/opencv.hpp>
#include "Libraries/Image.h"
#include "Libraries/Matrix.h"
#include <iostream> 

using namespace std; 
using namespace cv;


int main(){
   
    Matrix image(246, 400);
    image.randomize(0.0f, 255.0f); 
    image.guassian_blur(13, 2.0f);
    image.invert();
    image.scale(5.0f);
    image.save_as_image("thing.png", true);
    // imshow("", image.to_mat());
    // cv::waitKey(0);
    // return 0;

}
