#include <iostream>
using namespace std;
#include "Entry.h"


#pragma once
class Sparse {
    public: 
        vector<Entry> entries;

        Sparse();
        Sparse(vector<Entry> entries);


        Sparse operator+(Sparse other);
        Sparse operator-(Sparse other);

        Sparse operator*(Q q);
        Sparse operator*(int z);
        Sparse operator/(Q q);
        Sparse operator/(int z);

        void add(Entry entry);
        void add(vector<int> index, float value);
        void add(vector<int> dim, vector<int> index, Q value);
};  


