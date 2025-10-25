#include <iostream> 
#include <vector>
#include "../Matrix/Matrix.h"
#include "../Tensor/Sparse.h"
#include "Map.h"
using namespace std;

// Ratio of Multivariate Polynomials

#pragma once
class Function {
    public: 
        float center;
        // float scale ???...

        Sparse alpha;
        Sparse beta = Sparse({Entry({0}, {0}, 1.0f)});

        // textual input
        Function(string alpha);
        Function(string alpha, float center);
        Function(string alpha, string beta); 
        Function(string alpha, string beta, float center); 
        

        // non textual input as well
        Function(Sparse alpha);      
        Function(Sparse alpha, Sparse beta); 

        // ........................................
        Function plus(Function function);
        Function operator+(Function f);
        Function operator-(Function f);
        Function operator*(Function f);
        vector<Function> operator/(Function f);
        Function operator^(int power);


        void flip();


        vector<Function> group(int dim); // group vs factor?.... maybe reserved factor for acutally polynomial factorization?...



        Function operator*(float scale); 
        Function operator/(float scale);

        float deg();
        float deg(int dim);
        static float at(Sparse Sparse, vector<float> x); 
        float at(vector<float> x); 
        vector<Matrix> sample(vector<float> a, vector<float> b, vector<float> delta);
        void print(int n);
};


// factoring a polynomial?... w/ root finding?... other algos?...


// partial at method?... returns function...
// compound operators 
// expand polynomial w/ center
// factor wrt to a variable
// LCD GCF of polynomial etc... 
// long & synthetic division now w/ multivariate polynomials
// derivative & integral now w/ mvp
// composite mvp
// sampling mvps
// power method?... repeated multiplication, negative exponent means flip. then multiply & stuff...
// Partial Fraction Decompoistion
// integral function
// limits? limit of infite?
// e.g. 0, inf, or ratio of leading ceofficients




// Q + R/P format rather than 
// p/q ?... idk...