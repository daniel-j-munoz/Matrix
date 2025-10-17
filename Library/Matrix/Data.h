// Hnadles data preprocessing
// and data manipulation and stuff.

// also handle stats?....

#include "Matrix.h"

class Data {



    public: 
        static float sum(Matrix A);
        static void power(float power, Matrix* A);
        static void absolute(Matrix* A);


        
        static vector<float> max(Matrix A);
        static vector<float> min(Matrix A);
        static vector<int> knn(float x);    // just indices, or values as well?...
        static int nn(float x, Matrix A);     // just nearest neightbor?...
        static float threshold();


        static Matrix swap(Matrix A, vector<float> swap);


        // find values from greaetest to least as well?
        // not just sort?...


        // sort shuffle?...




        // knn for vectors as well??....
        


        // Unitizing and Zeroing 
        // normalizing and stuff....
        static void unit_L(float p, Matrix *A);
        static void unit_L2(Matrix *A);



        static void range(float a, float b, Matrix* A);
        static void range(float a, float b, float c, float d, Matrix* A);


        static Matrix to_matrix(vector<float> entries);

};