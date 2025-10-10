#include "../Matrix/Matrix.h"
#include "Peice.h"
#include "Function.h"

class Interpolate{


    public: 
        // static Peice natural_spline(Matrix nodes); 
        // static vector<vector<float>> create_spline_system(vector<float> x, vector<float> y, vector<float> H);

        static Function lagrange(Matrix data, int n);
        static Peice peice_wise_lagrange(Matrix data, int n);
};

// ask calude/gpt if there is a more straightfoward algo?



// bezier? ....
// implement lagrange? ....