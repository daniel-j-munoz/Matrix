#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


// call packages insead?....
#include "Library/Matrix/Matrix.h"
#include "Library/Matrix/Eigen.h"
#include "Library/Matrix/Solve.h"
#include "Library/Matrix/Factor.h"
#include "Library/Function/Peice.h"
#include "Library/Function/Interpolate.h"
#include "Library/Function/Graph.h"
#include "Library/Function/Fit.h"



int main(){





    Matrix data(
        12, 2, 
        {
            -5, 1,
            -4, 2, 
            -3, 3, 
            -2, 4, 
            -1, 5,
            0, 4,
            1, 3,
            2, 2, 
            3, 1, 
            4, -2, 
            5, -3,
            6, -4
        }
    );

    Matrix dsd(
        3, 2, 
        {
            -5, -1,
            0, -3,
            5, 4
        }
    );


    Peice l = Interpolate::peice_wise_lagrange(data, 2);

   


    Graph graph(1000, 1000);
    graph.graph(data);
    graph.graph(l.sample(-5, 6, 0.5f));
    graph.show();


    return 0;

}












//     // call upperhessenberg on symmetric.
//     // lu of symmetric? triadigonal? etc....

//     vector<Matrix> LU = Factor::LU(A); 
//     LU.at(0).print(2); 
//     LU.at(1).print(2); 
//     (LU.at(0) * LU.at(1)).print(2);





// downsampling? vec or mat?