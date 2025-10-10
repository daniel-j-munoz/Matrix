#include "Fit.h"

Function Fit::polynomial(Matrix data, int n){
    Matrix x = data.get_column(0);
    Matrix y = data.get_column(1);

    // vandermonde matrix
    Matrix X(x.M, n + 1, 0.0f);
    for(int j = 0; j < x.M; j++){
        for(int i = 0; i <= n; i++){
            X.set(j, i, pow(x.data.at(j), i)); 
        }
    }

    Matrix A = (X.T() * X).invert();
    Matrix B = X.T() * y;
    Matrix beta = A * B;
    return Function(beta.data, 0.0f);
}

// one w/ out vandermonde matrix. and its just x in each row. 
// so it's like a linear model with multiple betas and stuf..

// pade approximation?...
// taylor series...?...