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



    Function a({5, 0, 3, 7});

    float area = Area::guass_legendre(a.sample(-5, 5, 0.1f));




    // Function f({1, 1, 1, 1}, 2);
    // f.print(0);


    // Root::newton_horner({0, 0, 0}, f).T().print(2);


    // f.derivative().print(0);

    return 0;

}





