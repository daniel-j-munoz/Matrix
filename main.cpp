#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;





#include "Library/Tensor/Sparse.h"
#include "Library/Function/Function.h"

// does foil handle negative exponents right?/...

#include "Library/Function/Q.h"




int main(){



    Sparse s(
        {{0, 1}, {0, 1}}, // shells
        {{1, 1}, {1, 1}}, // points
        {Q(3, 5), Q(0, 0)} // numbers
    );

    















    // Variable::create_map();


    // Sparse alpha;
    // alpha.add({0}, {0}, 5.0f); 
    // alpha.add({0}, {2}, -1.0f);
    // alpha.add({1}, {-1}, 1.0f);
    

    // vector<Function> beta;
    // Function f(alpha);

    // (f^3 * g^2).print(0);





    /**
     * 
     * Function alpha;
     * vector<Function> beta;
     * Function::PFD(alpha, beta)
     * 
     * PFD(){
     * 
     *      vector<Function> 
     *      
     * }
     * 
     * 
     */












    return 0;

}






    // polynomial w/ float as exponents?....
    // intersting...