// solve system of eqatuions 
// direct and numerical methods?.....

// Jacobi itertation/method 
// Guass sediel.

// nonlinear jacobi and guass seidel?...

#include "Matrix.h"

class Solve {



    public:  
        Solve(); 


        static Matrix gauss_seidel(Matrix A, Matrix x, float w);
        static Matrix rref(Matrix A); // return copy or edit instead?...    // partial pivoting... scaled pivoting... differnt methods?.... Chapter 6 Numerical Analysis Burden & Faires

        static Matrix conjugate_gradient(Matrix A, Matrix x); 


};