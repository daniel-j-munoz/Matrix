#include "Matrix.h"

// Diagonalize, LU, SVD etc...
class Factor {
    public: 
        static vector<Matrix> QR(Matrix A);
        static vector<Matrix> QRHH(Matrix A);

        // generalize LU Decomp to PLU. 
        // which just gives an additional permutation matrix 
        // to handle the cases of zero pivots.
        // pretty straightfoward...
        
        // u can also use it for partial pivoting. which basically just means 
        // instead of just finding a non zereo pivot.
        // u choose the one w/ the largest absolute magnitude. which improves num stab and stuff like that i think....
        static vector<Matrix> LU(Matrix A);
        static vector<Matrix> cholesky(Matrix A);
        // Just return L? 

};