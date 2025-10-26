#include <iostream>
using namespace std;
#include "../Function/Q.h"

// sparse.list?.. yes no?...
// can have negative points & stuff..

#pragma once
class Sparse {
    public: 
        vector<vector<int>> shells = {};
        vector<vector<int>> points = {};
        vector<Q> numbers = {};


        Sparse();
        Sparse(vector<vector<int>> shells, vector<vector<int>> points, vector<Q> numbers);


        Sparse operator+(Sparse other);
        Sparse operator-(Sparse other);

        Sparse operator*(Q q);
        Sparse operator*(int z);
        Sparse operator/(Q q);
        Sparse operator/(int z);


        void add(vector<int> index, float value);
        void add(vector<int> shell, vector<int> point, Q number);



        static void sort(vector<int>* a, vector<int>* b);
        static void remove_zeros(vector<int>* shell, vector<int>* point); 

        static bool origin(vector<int> shell);// call at origin?... idk... other names?>...
        static void form(vector<int>* shell, vector<int>* point);
        static bool equal(vector<int>* shell, vector<int>* point, vector<int>* next_shell, vector<int>* next_point);

};  


