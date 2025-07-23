#include <opencv2/opencv.hpp>
#include "Libraries/Image.h"
#include "Libraries/Matrix.h"
#include <iostream> 

using namespace std; 
using namespace cv;


int main(){
   
    Matrix image(1080, 1080);
    image.randomize(0.0f, 255.0f); 
    imshow("", image.to_mat());
    cv::waitKey(0);
    return 0;

}
