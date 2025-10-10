#include "Matrix.h"

// Diagonalize, LU, SVD etc...
class Factor {
    public: 
        static vector<Matrix> QR(Matrix A);
        static vector<Matrix> QRHH(Matrix A);
        static vector<Matrix> LU(Matrix A);
        static vector<Matrix> cholesky(Matrix A);
        // Just return L? 
};