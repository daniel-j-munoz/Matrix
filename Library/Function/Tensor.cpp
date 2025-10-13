#include "Tensor.h"



Tensor::Tensor(vector<int> shape){
    vector<int> shift = {}; 

    // Find Max shift 
    int total_size = 1; 
    for(int size : shape){
        total_size *= size; 
    }
    vector<float> data = vector<float>(total_size, 0.0f);

    // Calculate Strides 
    int stride = 1; 
    shift.insert(shift.begin(), 1);
    int start = shape.size() - 2;
    for(int i = start; i >= 0; i--){
        stride *= shape[i + 1];
        shift.insert(shift.begin(), stride);
    }

    this->shape = shape; 
    this->shift = shift; 
    this->data = data; 
}

float Tensor::get(vector<int> index){
    int spot = 0; 
    for(int i = 0; i < index.size(); i++){
        spot += index[i] * shift[i];
    }
    return data[spot];
}

void Tensor::add(vector<int> index, float value){
    int spot = 0; 
    for(int i = 0; i < index.size(); i++){
        spot += index[i] * shift[i];
    }
    data[spot] += value;
}
