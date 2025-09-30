#include "Matrix.h"

// Diagonalize, LU, SVD etc...
class Factor {
    public: 
        static vector<Matrix> QR(Matrix A);
        static vector<Matrix> QRHH(Matrix A);
};