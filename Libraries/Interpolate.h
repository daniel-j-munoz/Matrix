#include "Matrix.h"
#include "Peice.h"

class Interpolate{


    public: 
        static Peice natural_spline(Matrix nodes); 
        static vector<vector<float>> create_spline_system(vector<float> x, vector<float> y, vector<float> H);
};

// ask calude/gpt if there is a more straightfoward algo?