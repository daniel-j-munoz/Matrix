#include "Matrix.h"

class Eigen {





    public: 
        Eigen();

        static Matrix QR(Matrix A);
        static void save_gershgorin(Matrix A, string name);

        // get gerhsgorin bounds?......
        // or get initial guess w/ gershgorin
};