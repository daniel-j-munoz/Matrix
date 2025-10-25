
#include "../Tensor/Sparse.h"



// Ratio of Complex Multivariate Polynomials.

#pragma once
class Function {
    public: 
        float center;

        Sparse terms;
        Function(Sparse terms);

        Function operator+(Function f);
        Function operator-(Function f);
        Function operator*(Function f);



















};



// + - * / ^
// inverse
// scale * /

// group, deg, 2 "at" methods, 
// sample 
// print