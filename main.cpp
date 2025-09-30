#include <opencv2/opencv.hpp>
#include "Libraries/Image.h"
#include "Libraries/Matrix.h"
#include <iostream>

using namespace std;
using namespace cv;


// call packages insead?....

#include "Libraries/Eigen.h"
#include "Libraries/Solve.h"

int main(){

    // vector<float> data = {
    //     5, -1, 2, 12, 
    //     3, 8, -2, -25, 
    //     1, 1, 4, 6
    // };
    // Matrix A(3, 4, data);

    vector<float> data = {
        10, -6, 0, 12,
        -6, 8, -2, 0, 
        0, -2, 5, 0
    };

    Matrix A(3, 4, data);


    data = {0, 0, 0};
    Matrix x(3, 1, data);

    // x = Solve::gauss_seidel(A, x, 1.0f);
    // x.print(2);


    x = Solve::conjugate_gradient(A, x);
    x.print(10);






}

