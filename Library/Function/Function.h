
#include "../Tensor/Sparse.h"




#pragma once
class Function {
    public: 
        float center;

        Sparse terms;
        Function(Sparse terms);

        Function operator+(Function f);
        Function operator-(Function f);
        Function operator*(Function f);
        vector<Function> operator/(Function f); // wrt to main variable?...
        // returns quotient & remainder. remainder doesnt have to be as ratio. 
        // or just return quoteint w/ remainder is zero?...... idk.......





        Function operator^(int power);

        void operator+=(Function f);
        void operator-=(Function f);
        void operator*=(Function f);
        void operator/=(Function f); 





        Function gcf(Function f);
        Function lcm(Function f);















};





// + - * / ^
// inverse
// scale * /

// group, deg, 2 "at" methods, 
// sample 
// print

// another class for single var polynomials or no?...

// decompose
// expand in terms of... 
// find expression using expansion in terms of...