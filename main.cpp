#include <opencv2/opencv.hpp>
#include "Libraries/Image.h"
#include "Libraries/Matrix.h"
#include <iostream>

using namespace std;
using namespace cv;

#include "Libraries/Eigen.h"

// Numerical Class here?....

// aitkens?...

int main(){


    vector<float> data = {
        1.0f, 3.0f, 3.0f,
        3.0f, 5.0f, 7.0f,
        3.0f, 7.0f, 6.0f
    };

    Matrix A(3, 3, data);




    
    // Matrix eigen = Eigen::QR(A);


    Matrix b(3, 1);
    b.randomize(-10.0f, 10.0f);
    Matrix eigenvector = Eigen::power(A, b);
    // eigenvector.print(2);





    return 0;
}




