// derivatives in here?

#include "Function.h"

class Area {

    public: 
        static float newton_cote(Matrix data, int n);
        float sum(); // ?


        
        static float guass_legendre(Matrix data);

        // takes in data of assumed interval a to b. 
        // edits range to be -1 to 1
        // and integrtes from -1 to 1. 

        static Function legendre(int n);



        // integrate cubic spline function?


        // put legendre & chebsyev polynomials creation in another class?...

};




// monte carlo integration. 
// higher dimesnions...
// imporoper integerals?...