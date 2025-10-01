#include "Matrix.h"

class Interpolate{


    public: 


        static Matrix cubic_spline(Matrix data);

        static Matrix natural_spline(Matrix x, Matrix y); 

        // natural, clamped?
        // just name spline instead? e.g. spline()?
};