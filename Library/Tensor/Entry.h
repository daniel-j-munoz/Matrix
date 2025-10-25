
#include <iostream>
#include <vector>
using namespace std;
#include "../Function/Map.h"

#pragma once
class Entry {

    public: 
        vector<int> dim = {}; 
        vector<int> index = {};  // store as matrix?... for dim and index?....
        float value;

        Entry(vector<int> dim, vector<int> index, float value);

        static bool equal(Entry a, Entry b);

};