#include <iostream> 
#include <vector> 
#include <algorithm>

using namespace std;

// you can have neagtive point and stuff..

class Monomial {

    public: 
        
    // this could be varaibles 
    // and powers now....
    // but i still kind of like the name shell and point
    // they're pretty convient... idk...
        vector<int> shell; 
        vector<int> point; 

        int number;

        Monomial(vector<int> shell, vector<int> point, int number);

        Monomial operator*(int x);
        Monomial operator*=(int x);
        Monomial operator*(Monomial other);
        Monomial operator/(Monomial other);



        bool divides(Monomial other);

        // other operations w/ monomials?......



        // Monomial operator


        int deg(int dim);
        Monomial coefficent(int dim);



        void sort();
        void remove_zeros();
        void form();
        bool constant();
        bool operator==(Monomial other);
        bool like_terms(Monomial other);
};