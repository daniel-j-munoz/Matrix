
#include <iostream>
#include <vector>
using namespace std;

#include "../Function/Q.h"

#pragma once
class Entry {

    public: 
        vector<int> dim = {}; 
        vector<int> index = {};  // store as matrix?... for dim and index?....
        Q value = Q(0, 0);

        Entry(vector<int> dim, vector<int> index, Q value);

        static bool equal(Entry a, Entry b);

};