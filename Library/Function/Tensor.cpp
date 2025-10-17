#include "Tensor.h"
#include "../Matrix/Data.h"


Tensor::Tensor(vector<float> shape){
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

Tensor::Tensor(vector<float> shape, float value){
    vector<int> shift = {}; 

    // Find Max shift 
    int total_size = 1; 
    for(int size : shape){
        total_size *= size; 
    }
    vector<float> data = vector<float>(total_size, value);

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

Tensor::Tensor(vector<float> shape, vector<float> data){
    vector<int> shift = {}; 

    // Find Max shift 
    int total_size = 1; 
    for(int size : shape){
        total_size *= size; 
    }

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


// makep oint a row vector insead?.... idk....
Matrix Tensor::point(int i){
    int order = shape.size(); // # dimensions
    vector<float> point(order, 0);
    for(int nth = 0; nth < order; nth++){
        point[nth] = i / shift[nth]; 
        i %= shift[nth];
    }
    return Matrix(point.size(), 1, point);
}


Tensor Tensor::operator+(Tensor other){
    Tensor output(shape);
    if(same_shape(other)){
        for(float i = 0; i < data.size(); i++){
            output.data[i] += data[i] + other.data[i];
        }
    }
    return output;
}

Tensor Tensor::operator-(Tensor other){
    return (*this) + (other * -1.0f);
}


Tensor Tensor::operator*(float scale){
    Tensor output = *this;
    for(int i = 0; i < data.size(); i++){
        data[i] *= scale;
    }
    return output;
}


bool Tensor::same_shape(Tensor tensor){
    if(shape.size() == tensor.shape.size()){
        for(int i = 0; i < shape.size(); i++){
            if(!(shape[i] == tensor.shape[i])){
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}


// print shape method?...
// print other things as well?....


// just call shape?...
void Tensor::print_shape(){
    for(float size : shape){
        cout << to_string((int)(size)) << " ";
    }
    cout << "\n";
}


// set rank?... new rank?...
Tensor Tensor::rerank(float rank){
    vector<float> shape = this->shape; 
    for(int i = 0; i < rank; i++){
        shape.push_back(1.0f);
    }

    Tensor output(shape);

    for(int i = 0; i < data.size(); i++){
        vector<float> index = point(i).data;
        for(int j = 0; j < rank; j++){
            index.push_back(0.0f);
        }
        output.add(index, data[i]);
    }

    return output;
}

    // store indices in matrix
    // and data in vector or suM?...
    // then set data.... if u want to do void instead of copy?...




// ............ more ....................................

float Tensor::get(vector<float> index){
    int spot = 0; 
    for(int i = 0; i < index.size(); i++){
        spot += index[i] * shift[i];
    }
    return data[spot];
}

// set ...?

void Tensor::add(vector<float> index, float value){
    int spot = 0; 
    for(int i = 0; i < index.size(); i++){
        spot += index[i] * shift[i];
    }
    data[spot] += value;
}


/**
 * # of dimensions
 */
int Tensor::rank(){
    return shape.size();
}



Tensor Tensor::T(vector<float> swap){
    Matrix shape = Data::swap(Data::to_matrix(this->shape), swap);
    Tensor output(shape.data);

    for (int i = 0; i < output.data.size(); i++) {
        Matrix index = Data::swap(output.point(i), swap);
        output.data[i] = get(index.data);
    }
    
    return output;
}


// assumes ranks are equal...
// can help for compaiblltiy between tensors & stuff. 

// rehspaes everything to max shape basically...
void Tensor::make_union(vector<Tensor*> tensors){
    vector<float> shape = {};
    for(int i = 0; i < tensors[0]->rank(); i++){
        float size = -1;
        for(int j = 0; j < tensors.size(); j++){
            size = max(size, tensors[j]->shape[i]);
        }
        shape.push_back(size);
    }

    for(Tensor* tensor : tensors){
        tensor->reshape(shape);
    }
}


void Tensor::reshape(vector<float> shape){

    cout << "as;lfjkasf";
}