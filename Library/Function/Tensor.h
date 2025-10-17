#include <iostream>
using namespace std;


#include "../Matrix/Matrix.h"

// remove tesnor from function folder?...

class Tensor {


    public: 
        vector<float> shape = {};
        vector<int> shift = {};
        vector<float> data = {};

        Matrix point(int i); // return vector. aka point in space in a way...


        Tensor subspace(vector<float> point, float z); // gets subpace of data. 
        // think of it like at this point. vary dimenion z and get all of those points.


        Tensor subspace(vector<float> point, vector<float> free); // vary the dimensions specifed in free. and hold point constnat(excluding the dimensions specified.)



        Tensor T(vector<float> swap); // void or copy?...

        Tensor(vector<float> shape);
        Tensor(vector<float> shape, float value);
        Tensor(vector<float> shape, vector<float> data);


        Tensor operator+(Tensor other);
        Tensor operator-(Tensor other);
        Tensor operator*(float scale);

        float get(vector<float> index);
        void add(vector<float> index, float value);


        void reshape(vector<float> shape);

        int rank();




        // rehsape idk?...
        Tensor rerank(float shape); // more dimensoins/axes.  void or copy?... maybe void instead for this one?...
        Tensor rerank_reshape(); // append new shape?....


        bool same_shape(Tensor tensor);

        static void make_union(vector<Tensor*> tensors);


        void print_shape();
};  