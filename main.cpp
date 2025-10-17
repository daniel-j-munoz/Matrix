#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

#include "Library/Function/Peice.h"
#include "Library/Function/Interpolate.h"
#include "Library/Function/Graph.h"
#include "Library/Function/Fit.h"
#include "Library/Matrix/Matrix.h"
#include "Library/Matrix/Eigen.h"
#include "Library/Matrix/Solve.h"
#include "Library/Matrix/Factor.h"
#include "Library/Function/Root.h"
#include "Library/Function/Area.h"


int main(){

    Tensor data = Tensor({3, 3});
    data.add({0, 0}, 1.0f); // x^0
    data.add({1, 0}, 3.0f); // x^1
    data.add({2, 0}, 5.0f); // x^2
    
    data.add({0, 0}, 4.0f); // y^0
    data.add({0, 1}, 3.0f); // y^1
    data.add({0, 2}, 2.0f); // y^2

    
    Function a(data);
    a.map.add("a", 0);
    a.map.add("b", 1);

    Function b(data);
    b.map.add("x", 0);
    b.map.add("y", 1);





    Function c = (a.plus(b));
    // c.print(2);





    return 0;

}








    // Function f({1, 1, 1, 1}, 2);
    // f.print(0);
    // Root::newton_horner({0, 0, 0}, f).T().print(2);
    // f.derivative().print(0);
