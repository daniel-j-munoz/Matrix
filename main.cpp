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


    // Matrix b(3, 1);
    // b.randomize(-10.0f, 10.0f);
    // Matrix eigenvector = Eigen::power(A, b);
    // eigenvector.print(2);



    vector<Matrix> QR = A.QRHH(); 
    QR.at(0).print(2);
    cout << "\n";
    QR.at(1).print(2);


    cout << "\n";
    (QR.at(0) * QR.at(1)).print(2);


    return 0;
}



// Min(m - 1, n) iterations? hhoulder method?...
