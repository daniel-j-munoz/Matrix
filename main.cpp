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
#include "Libraries/Interpolate.h"
#include "Libraries/Peice.h"
#include "Libraries/Graph.h"




#include <chrono>  // for timing
#include <iomanip> // for formatting output
using namespace chrono;



int main(){


    vector<float> data = {
        -3, 6, 
        -2, 12, 
        -1, 0, 
        0, 3, 
        1, 4, 
        2, 2, 
        3, 9
    };

    Matrix nodes(7, 2, data);


    Peice spline = Interpolate::natural_spline(nodes);

    Graph graph(1000, 1000);
    // graph.graph(nodes); 
    graph.graph(spline.sample(-3, 3, 0.25f));
    graph.show(); 
  

    

    return 0;

}












//     // call upperhessenberg on symmetric.
//     // lu of symmetric? triadigonal? etc....

//     vector<Matrix> LU = Factor::LU(A); 
//     LU.at(0).print(2); 
//     LU.at(1).print(2); 
//     (LU.at(0) * LU.at(1)).print(2);


