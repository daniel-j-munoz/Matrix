#include <iostream>
using namespace std;

// remove tesnor from function folder?...

class Tensor {


    public: 
        vector<int> shape = {};
        vector<int> shift = {};
        vector<float> data = {};

        Tensor(vector<int> shape);

        float get(vector<int> index);
        void add(vector<int> index, float value);
};  