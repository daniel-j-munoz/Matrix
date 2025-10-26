
#include "../Tensor/Sparse.h"




#pragma once
class Function {
    public: 
        float center;

        // vector<monomial> monomials = {};

        

        // Sparse terms;
        // monomials?...

        Function(Sparse terms);

        Function operator+(Function f);
        Function operator-(Function f);
        Function operator*(Function f);
        vector<Function> operator/(Function f); // wrt to main variable?...
        // returns quotient & remainder. remainder doesnt have to be as ratio. 
        // or just return quoteint w/ remainder is zero?...... idk.......





        Function operator^(int power);


        // compound operators
        void operator+=(Function f);
        void operator-=(Function f);
        void operator*=(Function f);
        void operator/=(Function f); 
        void operator^=(int n);


        int max_deg(int dim);
        int min_deg(int dim);
        vector<Function> group(int dim);


        static Function monomial_product(vector<int> shell, vector<int> point, Q number, vector<int> next_shell, vector<int> next_point, Q next_number);

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

// lc, lm?... leading coeff, leading monomial?>..