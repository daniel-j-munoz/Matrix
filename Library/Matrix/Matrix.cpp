#include "Matrix.h"

#include <random>
#include <fstream>
#include <string>

#include "Data.h"
#include "Factor.h"
#include "Solve.h"

/**
 *  @param values row major order 
 * */
Matrix::Matrix(int M, int N, vector<float> values){
    this->data = {};
    this->M = M; 
    this->N = N;
    for(int ith = 0; ith < M * N; ith++){
        data.push_back(values[ith]);
    }
}

/** @param value init w/ value */
Matrix::Matrix(int M, int N, float value){
    this->data = {};
    this->M = M; 
    this->N = N;
    for(int i = 0; i < M * N; i++){
        data.push_back(value);
    }
}

/**
 * Identity Matrix
 */
Matrix::Matrix(int M, int N){
    this->data = {};
    this->M = M; 
    this->N = N;
    data = vector<float>(M * N, 0.0f);
    for(int m = 0; m < M; m++){
        for(int n = 0; n < N; n++){
            int ith = N * m + n;
            if(m == n){
                data[ith] = 1.0f;
            } else {
                data[ith] = 0.0f; 
            }
        }
    }
}

// ............. 2D ..................................... 

// void or copy?
Matrix Matrix::operator*(float scale){
    Matrix output = *this;
    output.scale(scale);
    return output;
}

Matrix Matrix::operator*=(float scale){
    *this = *this * scale;
    return *this;
}

// replace scale method w/ operator instead?
void Matrix::scale(float scalar){
    for(int ith = 0; ith < data.size(); ith++){
        data[ith] *= scalar;
    }
}

Matrix Matrix::operator*(Matrix& other) {
    if (N != other.M) {
        throw std::invalid_argument("Matrix dimensions incompatible for multiplication");
    }
    
    Matrix result(M, other.N, 0);
    
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < other.N; n++) {
            float dot_product = 0.0f;
            
            for (int i = 0; i < N; i++) {
                dot_product += get(m, i) * other.get(i, n);
            }
            
            result.set(m, n, dot_product);
        }
    }
    
    return result;
}

Matrix Matrix::operator*=(Matrix& other){
    *this = *this * other;
    return *this;
}

float Matrix::TRIDET(){
    float prod = 1.0f;
    for(int i = 0; i < N; i++){
        prod *= get(i, i);
    }
    return prod;
}

float Matrix::DET(){
    vector<Matrix> LU = Factor::LU(*this);
    float det = pow(-1.0f, LU.at(0).count_swaps());
    det *= LU.at(1).TRIDET();
    det *= LU.at(2).TRIDET();
    return det;
}

Matrix Matrix::invert(){
    return Solve::LU(*this, Matrix(M, N));
    // if triangular. simply solve via backsub. 
    // thats why tags could be very useful.
    // if symmetric we could do cholesky as well. 
    // which i belive is like twice as efficent & stuff..
    // tags could be very helpful. just writing what comes to head..
}

Matrix Matrix::T() {
    vector<float> temp(M * N, 0);
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            temp[M * n + m] = get(m, n);
        }
    }

    return Matrix(N, M, temp);
}

void Matrix::square(int size){
    resize(size, size);
}

// does % work here?
Matrix* Matrix::ROI(int row, int col, int next_row, int next_col){
    Matrix* output = new Matrix(next_row - row + 1, next_col - col + 1, 0);
    for(int m = row; m <= next_row; m++){
        for(int n = col; n <= next_col; n++){
            output->set(m - row, n - col, get(m % M, n % N));
        }
    }
    return output; 
}

Matrix Matrix::project(Matrix v){
    Data::unit_L2(&v);
    v.scale(dot(v));
    return v;
}

Matrix Matrix::element_wise(Matrix& other, char operation){

    // Exception
    if(!(M == other.M && N == other.N)){
        cout << "Size Mismatch "; 
        cout << M << ", " << N << " & " << other.M << ", " << other.N << "\n";
        throw invalid_argument("");
    }

    // Element Wise
    vector<float> new_data = {};
    for(int ith = 0; ith < other.data.size(); ith++){
        if(operation == '*'){
            new_data.push_back(this->data[ith] * other.data[ith]);
        } else if(operation == '+'){
            new_data.push_back(this->data[ith] + other.data[ith]);
        } else if(operation == '-'){
            new_data.push_back(this->data[ith] - other.data[ith]);
        } else if(operation == '/'){
            new_data.push_back(this->data[ith] / other.data[ith]);
        }
        // exponent? 
    }

    return Matrix(M, N, new_data);
}

Matrix Matrix::operator+(Matrix& other){
    return element_wise(other, '+');
}

Matrix Matrix::operator+=(Matrix& other){
    *this = *this + other;
    return *this;
}

Matrix Matrix::operator-(Matrix& other){
    return element_wise(other, '-');
}

Matrix Matrix::operator-=(Matrix& other){
    *this = *this - other;
    return *this;
}

// any size. just need same # of elements and stuff...
float Matrix::dot(Matrix& other){
    float sum = 0.0f;
    for(int i = 0; i < data.size(); i++){
        sum += other.data[i] * data[i];
    }
    return sum;
}

float Matrix::L2(){
    return L(2);
}

float Matrix::L(float p){
    Data::absolute(this);
    Data::power(p, this);
    return pow(Data::sum(*this), 1.0f / p);
}

/**
 * L Infinite Norm
 */
float Matrix::LI(){
    Data::absolute(this);
    return Data::max(*this)[0];
}




// .............................. Set Add & Get Methods ............................................................................................
void Matrix::set(int m, int n, float value){
    data[N * m + n] = value; 
}

float Matrix::get(int m, int n){
    return data[N * m + n];
}

Matrix Matrix::get_row(int m){
    vector<float> new_data = {}; 
    for(int n = 0; n < N; n++){
        new_data.push_back(get(m, n));
    }
    return Matrix(1, N, new_data);
}

void Matrix::add_row(vector<float> values){
    M++; 
    for(float value : values){
        data.push_back(value);
    }
}

Matrix Matrix::get_column(int n){
    vector<float> new_data = {}; 
    for(int m = 0; m < M; m++){
        new_data.push_back(get(m, n));
    }
    return Matrix(M, 1, new_data);
}

void Matrix::add_column(vector<float> values){
    vector<float> new_data;
    for(int m = 0; m < M; m++){
        for(int n = 0; n < N; n++){
            new_data.push_back(get(m, n));
        }
        new_data.push_back(values[m]);
    }
    
    N++;
    data = new_data;
}

void Matrix::add_column(Matrix column){
    add_column(column.data);
    // doesn't have to adhere to being column vector
    // maybe its fine to input any matrix. just let it input the data of that matrix?...
    // idk... interseting.....
}



void Matrix::to_row_vector(){
    N = M * N;
    M = 1; 
}

void Matrix::to_column_vector(){
    M = M * N;
    N = 1; 
}

void Matrix::reshape(int m, int n){
    M = m; 
    N = n;
}





// ensure it handles shrinking and expanding correctly. 
void Matrix::resize(int m, int n) {
    vector<float> new_data(m * n, 0);
    
    int copy_rows = std::min(M, m);
    int copy_cols = std::min(N, n);
    
    for (int row = 0; row < copy_rows; ++row) {
        for (int col = 0; col < copy_cols; ++col) {
            new_data[row * n + col] = data[row * N + col];
        }
    }
    
    M = m;
    N = n;
    data = new_data;
}

Matrix Matrix::copy(){
    return Matrix (M, N, this->data); 
}

void Matrix::print(int x) {
    cout << fixed << setprecision(x);

    for(int m = 0; m < M; m++){
        for(int n = 0; n < N; n++){
            cout << get(m, n) << " ";
        }
        cout << "\n";
    }
    cout << defaultfloat; 
    cout << "\n";
}


























// gpt gen. how does this work? 
float Matrix::count_swaps(){
    vector<int> perm(N);
    
    // Extract permutation π: row index of 1 in each column
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < N; ++i) {
            if (get(i, j) == 1.0f) {
                perm[j] = i;
                break;
            }
        }
    }

    // Count inversions (number of swaps)
    int swaps = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (perm[i] > perm[j]) swaps++;
        }
    }
    return swaps;
}




void Matrix::add_matrix(Matrix B){
    for(int i = 0; i < B.N; i++){
        Matrix col = B.get_column(i);
        add_column(col);
    }
}