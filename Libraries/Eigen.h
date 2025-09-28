#include "Matrix.h"

class Eigen {





    public: 
        Eigen();


        static Matrix QR(Matrix A);
        static Matrix power(Matrix A, Matrix b); 
        static void save_gershgorin(Matrix A, string name);


        // get gerhsgorin bounds?......
        // or get initial guess w/ gershgorin
        // perhaps gershgorin serves as good intial guess?...

        // QR w/ shifting ... ?... 
        // i knkow there is like alteranvites w/ like shifting and stuff...
};