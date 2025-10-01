#include <opencv2/opencv.hpp>
#include "Libraries/Image.h"
#include "Libraries/Matrix.h"
#include <iostream>

using namespace std;
using namespace cv;


// call packages insead?....

#include "Libraries/Eigen.h"
#include "Libraries/Solve.h"
#include "Libraries/Factor.h"


int main(){

    vector<float> data = {
        4, 12, -16, 
        12, 37, -43, 
        -16, -43, 98
    };

   Matrix A(3, 3, data);

   vector<Matrix> LLT = Factor::cholesky(A);

   LLT.at(0).print(2);
   LLT.at(1).print(2);



}












//  vector<float> data = {
//         5, 2, 1, 4, 5, 
//         3, 5, 2, 8, 2, 
//         1, 2, 3, 2, 4, 
//         5, 2, 3, 2, 5, 
//         2, 3, 5, 2, 1,
//     };
//     Matrix A(5, 5, data);


//     Matrix AT = A.T();
//     A = A * AT;

//     A = A.upper_hessenberg();
//     A.print(2);

//     // vector<float> data = {
//     //     10, -6, 0, 12,
//     //     -6, 8, -2, 0, 
//     //     0, -2, 5, 0
//     // };

//     // Matrix A(3, 4, data);


//     // data = {0, 0, 0};
//     // Matrix x(3, 1, data);

//     // x = Solve::gauss_seidel(A, x, 1.0f);
//     // x.print(2);


//     // x = Solve::conjugate_gradient(A, x);
//     // x.print(10);


//     // call upperhessenberg on symmetric.
//     // lu of symmetric? triadigonal? etc....

//     vector<Matrix> LU = Factor::LU(A); 
//     LU.at(0).print(2); 
//     LU.at(1).print(2); 
//     (LU.at(0) * LU.at(1)).print(2);


