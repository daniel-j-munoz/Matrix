#include "Monomial.h"

// before we maybe replace int w/ q..
// save previous version 
// and make sure Q is handled a lot better first?...
// like handling irrational stuff and all of that
// then implemenent when handled better?>....


// think of function as a mult var polynomial 
// and its sort of like a sparse tensor in a way...
// w/ monomials acting like each element of the sparse tensor in a way....
// each var is like a new dim & each corresponding power is like an index in that axis/dim

#pragma once
class Function {
    public: 

        int wrt = 0;
        int power = 0;


        float center;
        // float gcd?...

        vector<Monomial> monomials = {};


        // lexisort method?...
        // that acheives lexographic order?...



        Function(vector<Monomial> monomials);

        Function operator+(Function f);
        Function operator-(Function f);
        Function operator*(Function f);
        vector<Function> operator/(Function f); // wrt to main variable?...
        // returns quotient & remainder. remainder doesnt have to be as ratio. 
        // or just return quoteint w/ remainder is zero?...... idk.......
        
        Function operator*(int x);
        Function operator/(int x);


        void lexisort();
        Monomial lm(); // leading monomial




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



        Function gcf(Function f);
        Function lcm(Function f);








        Function operator+(Monomial monomial);
        void operator+=(Monomial monomial);


        Function operator*(Monomial other);




        void print();





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