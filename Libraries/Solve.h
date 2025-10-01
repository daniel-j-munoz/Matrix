// solve system of eqatuions 
// direct and numerical methods?.....

// Jacobi itertation/method 
// Guass sediel.

// nonlinear jacobi and guass seidel?...

#include "Matrix.h"

class Solve {



    public:  


        static Matrix gauss_seidel(Matrix A, Matrix x, float w);
        static Matrix rref(Matrix A); // return copy or edit instead?...    // partial pivoting... scaled pivoting... differnt methods?.... Chapter 6 Numerical Analysis Burden & Faires


        // Create methods. foward and backsubsition...
        // LU will use them
        // and you can also use them, if your matrix is upper or lower triangular...
        static Matrix LU(Matrix A);

        static Matrix foward(); 
        static Matrix backward();


        static Matrix conjugate_gradient(Matrix A, Matrix x); 


};