#include "Matrix.h"

class Solve {
    public:  

        static Matrix LU(Matrix A, Matrix B);
        static Matrix cholesky(Matrix A, Matrix B);
        static Matrix foward(Matrix A, Matrix B); 
        static Matrix backward(Matrix A, Matrix B);
        static vector<Matrix> RREF(Matrix A, Matrix B); // copy or void?    
        static Matrix guass_back(Matrix A, Matrix B);

        // static Matrix thomas(Matrix A);
        // static Matrix thomas(vector<float> a, vector<float> b, vector<float> c, vector<float> d);
        // static Matrix conjugate_gradient(Matrix A, Matrix x); 
        // static Matrix gauss_seidel(Matrix A, Matrix X, float w);
        // nonlinear jacobi and guass seidel?...
};