#include "Matrix.h"

#include <random>
#include <fstream>
#include <string>



// ............. Constructors .....................................
Matrix::Matrix(int M, int N, vector<float>& values){
    this->data = {};
    this->M = M; 
    this->N = N;
    for(int ith = 0; ith < M * N; ith++){
        data.push_back(values[ith]);
        spectrum.push_back(complex<float>(values[ith], 0));
    }
}

Matrix::Matrix(int M, int N, float value){
    this->data = {};
    this->M = M; 
    this->N = N;
    for(int i = 0; i < M * N; i++){
        data.push_back(value);
        spectrum.push_back(complex<float>(value, 0));
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
// ................ Linear algebra operations and stuff ...............................................

// what if operator takes in a float for another version as well. 
// and can scale the vector/matrix or tensor or whatever... intereting....

Matrix Matrix::operator*(Matrix& other) {
    // Check dimensions for matrix multiplication
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

float Matrix::determinant(){
    if(N == 1){
        return data[0];
    }

    float sum = 0.0f; 
    int A = 1; 
    for(int n = 0; n < N; n++){
        Matrix subspace = *ROI(1, n + 1, M, n - 1);
        sum += A * get(0, n) * subspace.determinant(); 
        A *= -1; 
    }
    return sum;
}

// void Matrix::T(){
//     vector<float> temp(M * N, 0);
//     for(int m = 0; m < M; m++){
//         for(int n = 0; n < N; n++){
//             temp[N * n + m] = get(m, n);  
//         }
//     }

//     data = temp;

//     int temp_M = M;
//     M = N;
//     N = temp_M;
// }

// for some fucking reason. i don't know how but chatpgt managed to fix this
// and i dont' even know why this version works. what in the world?
// i think it was just that i should have used M instead of N for temp index. 
// but it works now i think


Matrix Matrix::T() {
    vector<float> temp(M * N, 0);
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            temp[M * n + m] = get(m, n);
        }
    }

    return Matrix(N, M, temp);
}


void Matrix::convolve(Matrix& kernel, bool flip){
    int F = flip ? -1 : 1;
    int half = kernel.M / 2;
    vector<float> temp(M * N, 0);
    for(int m = 0; m < M; m++){
        for(int n = 0; n < N; n++){
            float sum = 0.0f;
            for(int k = -half; k <= half; k++){
                for(int h = -half; h <= half; h++){
                    int x = n + h; 
                    int y = m + k;
                    if(
                        y >= 0 && y < M && 
                        x >= 0 && x < N
                    ){
                        sum += get(y, x) * kernel.get(half - F * k, half - F * h);
                    }
                }
            }
            temp[N * m + n] = sum;
        }
    }
    data = temp;
}

void Matrix::convolve_validd(Matrix& kernel, int new_m, int new_n, bool flip){
    int F = flip ? -1 : 1;
    int halfY = kernel.M / 2;
    int halfX = kernel.N / 2;

    // Starting positions to center the smaller output inside the full convolved result
    int offsetY = (M - new_m) / 2;
    int offsetX = (N - new_n) / 2;

    vector<float> temp(new_m * new_n, 0);

    for(int m = 0; m < new_m; m++){
        for(int n = 0; n < new_n; n++){
            float sum = 0.0f;
            int centerY = m + offsetY;
            int centerX = n + offsetX;

            for(int k = -halfY; k <= halfY; k++){
                for(int h = -halfX; h <= halfX; h++){
                    int y = centerY + k;
                    int x = centerX + h;
                    if (y >= 0 && y < M && x >= 0 && x < N){
                        sum += get(y, x) * kernel.get(halfY - F * k, halfX - F * h);
                    }
                }
            }
            temp[new_n * m + n] = sum;
        }
    }

    // Set new size and data
    this->M = new_m;
    this->N = new_n;
    this->data = temp;

}






// void Matrix::convolve_valid(Matrix& kernel, bool flip){
//     int F = flip ? -1 : 1;
//     int half = kernel.M / 2;
//     vector<float> temp(M * N, 0);
//     for(int m = 0; m < M; m++){
//         for(int n = 0; n < N; n++){
//             float sum = 0.0f;
//             for(int k = -half; k <= half; k++){
//                 for(int h = -half; h <= half; h++){
//                     int x = n + h; 
//                     int y = m + k;
//                     if(
//                         y >= 0 && y < M && 
//                         x >= 0 && x < N
//                     ){
//                         sum += get(y, x) * kernel.get(half - F * k, half - F * h);
//                     }
//                 }
//             }
//             temp[N * m + n] = sum;
//         }
//     }
//     data = temp;
// }



// does this work?
void Matrix::convolve_valid(Matrix& kernel, bool flip) {
    int half = kernel.M / 2;
    int out_M = M - kernel.M + 1;
    int out_N = N - kernel.N + 1;

    vector<float> temp(out_M * out_N, 0);

    for (int m = 0; m < out_M; m++) {
        for (int n = 0; n < out_N; n++) {
            float sum = 0.0f;

            for (int k = 0; k < kernel.M; k++) {
                for (int h = 0; h < kernel.N; h++) {
                    int y = m + k;
                    int x = n + h;

                    int kk = flip ? (kernel.M - 1 - k) : k;
                    int hh = flip ? (kernel.N - 1 - h) : h;

                    sum += get(y, x) * kernel.get(kk, hh);
                }
            }

            temp[out_N * m + n] = sum;
        }
    }

    // Update dimensions and data
    M = out_M;
    N = out_N;
    data = temp;
}

void Matrix::convolve_me(Matrix& kernel, bool flip) {
    int half = kernel.M / 2;
    int f = flip ? -1 : 1;
    vector<float> temp = data; // Start with original data
    
    // Only convolve the valid region (where kernel fits completely)
    for(int m = half; m < M - half; m++) {
        for(int n = half; n < N - half; n++) {
            float sum = 0.0f;
            for(int k = -half; k <= half; k++) {
                for(int h = -half; h <= half; h++) {
                    sum += get(m - k * f, n - h * f) * kernel.get(k + half, h + half);
                }
            }
            temp[m * N + n] = sum;
        }
    }
    
    data = temp;
}


 // what if you just return a vector of both? a vector w/ mask, shrinked and non shrinked.
    // or what if you can type it w/ string e.g. "Mask, Shrink" 
    // and it returns a mask and shrink in that order in a vector

void Matrix::max_pool(int size, bool mask) {
    int step = size; 
    int new_M = (M - size) / step + 1; 
    int new_N = (N - size) / step + 1; 
    vector<float> mask_data(M * N, 0.0f); 
    vector<float> new_data(new_M * new_N, 0.0f); 

    // Center
    for(int m = 0; m < new_M; m ++){
        for(int n = 0; n < new_N; n++){

            // Starting point
            int y = step * m; 
            int x = step * n; 

            // Max Pool
            float max = numeric_limits<float>::lowest(); 
            // int row_max, col_max; // i think having unitialized values was causing bugs ***************************************************************
            int row_max = y, col_max = x;  // Initialize to starting position 
            for(int k = 0; k < size; k++){
                for(int h = 0; h < size; h++){
                    int row = y + k; 
                    int col = x + h; 


                    if(get(row, col) > max){
                        max = get(row, col); 
                        row_max = row; 
                        col_max = col;
                    }
                }
            }

            if(mask){
                mask_data[N * row_max + col_max] = 1;
            } else {
                new_data[new_N * m + n] = max;
            }
        }
    }

    if(mask){
        data = mask_data; 
    } else {
        data = new_data; 
        M = new_M; 
        N = new_N;
    }

    
}


// so what if instead of a mean. we used a guassian? 
// so sort of weighted average basically
void Matrix::mean_pool(int size) {
    int stride = size; 

    // essentially measuring how many boxes you can fit in each direction given your stride and size lenght.
    int new_M = (M - size) / stride + 1; 
    int new_N = (N - size) / stride + 1; 
    vector<float> temp(new_M * new_N, 0.0f); 

    // Center
    for(int m = 0; m < new_M; m ++){
        for(int n = 0; n < new_N; n++){

            // Starting point
            int y = stride * m; 
            int x = stride * n; 

            // Max Pool
            float sum = 0.0f;
            for(int k = 0; k < size; k++){
                for(int h = 0; h < size; h++){
                    sum += get(y + k, x + h);
                    
                }
            } 
            temp[new_N * m + n] = sum / (size * size);
        }
    }

    data = temp; 
    M = new_M; 
    N = new_N; 
}



void Matrix::square(int size){
    resize(size, size);
}


// conv by seperability 
// how can we make these multiplicatinos and additions more efficient? 
// more effective? 

void Matrix::convolve_seperable(Matrix& A){

    // int size = A.data.size(); 
    // int half = (size - 1) / 2; 
    // Matrix horz(1, size, 0.0f); 
    // Matrix vert(size, 1, 0.0f);


    // Matrix A_T = A.T();
    // A.product(A_T);



    // // Horzitonal Convolution
    // for(int m = 0; m < M; m++){
    //     convolve_row(m, horz); 
    // }

    // // Vertical Convolution on intermediate image
    // for(int n = 0; n < N; n++){
    //     convolve_col(n, vert);
    // }

}

// of course we could probably use SVD for the kernel. 
// but then we have to rely on numerical methods and stuff. 
// but the guassian can be implemented in a more straightforward_pass manner w/ out having to do the SVD. 
// we can find the vert and horz of guassian w/ out having to use SVD

// but guassian blur in image instead or something? 
// since ti's more of an image method than matrix method?

// is 'A' nessecary? 
// ask gpt if it can be writen better?
void Matrix::guassian_blur(int size, float sigma){
    Matrix output(size, size, 0);

    float sigma_squared = pow(sigma, 2.0f); 
    float a = pow(2.0f * M_PI * sigma_squared, -1.0f);
    float A = pow(2.0f * M_PI * sigma_squared, -0.5f);
    int center = (size - 1) / 2; 
    
    Matrix horz(1, size, 0.0f); 
    Matrix vert(size, 1, 0.0f);

    float sum = 0.0f;
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            float input = pow(x - center, 2.0f) + pow(y - center, 2.0f);
            sum += a * exp(-0.5f / sigma_squared * input);
        }
    }

    // Horizontal & Vertical
    for (int ith = 0; ith < size; ith++) {
        float input = pow(ith - center, 2.0f);
        float value = A * exp(-0.5f / sigma_squared * input);
        horz.set(0, ith, value / sum); 
        vert.set(ith, 0, value); 
    }

    // Horzitonal Convolution
    for(int m = 0; m < M; m++){
        convolve_row(m, horz); 
    }

    // Vertical Convolution on Intermediate Image
    for(int n = 0; n < N; n++){
        convolve_col(n, vert);
    }
}

void Matrix::sep_conv_sobel_x(){
    vector<float> data;
    data = {-1, 0, 1};
    Matrix horz(1, 3, data); 
    data = {1, 2, 1};
    Matrix vert(3, 1, data);
    horz.scale(1.0f / 8.0f);  // scale or dont' scale?

    // create a sep conv method? takes in vert and horz components?
    // then create a get component for popular kernels like sobel and guassian
    // seperating a general kernel would require something like SVD i think

    // Horzitonal Convolution
    for(int m = 0; m < M; m++){
        convolve_row(m, horz); 
    }

    // Vertical Convolution on Intermediate Image
    for(int n = 0; n < N; n++){
        convolve_col(n, vert);
    }
}

void Matrix::sep_conv_sobel_y(){
    vector<float> data;
    data = {1, 2, 1};
    Matrix horz(1, 3, data); 
    data = {-1, 0, 1};
    Matrix vert(3, 1, data);
    horz.scale(1.0f / 8.0f); // scale or don't scale?

    // Horzitonal Convolution
    for(int m = 0; m < M; m++){
        convolve_row(m, horz); 
    }

    // Vertical Convolution on Intermediate Image
    for(int n = 0; n < N; n++){
        convolve_col(n, vert);
    }
}


/**
 * @param a horizontal kernel
 * @param b vertical kernel
 */
void Matrix::convolve_sep(Matrix& a, Matrix& b){
    // Horzitonal Convolution
    for(int m = 0; m < M; m++){
        convolve_row(m, a); 
    }

    // Vertical Convolution on Intermediate Image
    for(int n = 0; n < N; n++){
        convolve_col(n, b);
    }
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




void Matrix::FFT2D(){
    // Pre-allocate result matrices to avoid repeated add_column operations
    real_spectrum = new Matrix(M, N, 0.0f);
    imag_spectrum = new Matrix(M, N, 0.0f);
    
    // Temporary storage for row processing
    vector<complex<float>> row_data(N);
    
    // FFT on rows - process in-place to avoid copying
    for(int m = 0; m < M; m++){
        // Copy row data directly without creating Matrix object
        for(int n = 0; n < N; n++){
            row_data[n] = complex<float>(get(m, n), 0.0f);
        }
        
        // Perform FFT on row
        FFT(row_data);
        
        // Store results directly in pre-allocated matrices
        for(int n = 0; n < N; n++){
            real_spectrum->set(m, n, row_data[n].real());
            imag_spectrum->set(m, n, row_data[n].imag());
        }
    }
    
    // Temporary storage for column processing
    vector<complex<float>> col_data(M);
    
    // FFT on columns - process in-place
    for(int n = 0; n < N; n++){
        // Extract column data directly
        for(int m = 0; m < M; m++){
            col_data[m] = complex<float>(real_spectrum->get(m, n), imag_spectrum->get(m, n));
        }
        
        // Perform FFT on column
        FFT(col_data);
        
        // Store results back directly
        for(int m = 0; m < M; m++){
            real_spectrum->set(m, n, col_data[m].real());
            imag_spectrum->set(m, n, col_data[m].imag());
        }
    }
}

// i recall there only being n - 2 transformation from somewhere...

// Does this require the matrix to be squared?....

// i believe the matrix must be n x n. but im not sure...
/**
 * Returns as upper Hessenberg matrix
 * If symmetric, returns as tridiagonal matrix 
 * in both cases, the returned matrix retains eigenvalues/eigenvectors 
 * aka the matrix is similar.
 * 
 * there might be some exceptions that i am possibly unaware of.
 * i am not sure...
 * 
 * can be used as a good intial starting point for QR algorithms
 */
Matrix Matrix::upper_hessenberg(){
    Matrix A = *this;

    for(int k = 0; k < N - 2; k++){ 
        Matrix x = A.get_column(k); 

        // Zeros
        for(int i = 0; i <= k; i++){
            x.set(i, 0, 0.0f);
        }

        // Standard Basis & Get Vector 
        float sign = (x.get(k + 1, 0) >= 0) ? 1.0f : -1.0f; /// NEW STEP HERE
        Matrix b(M, 1, 0.0f);
        b.set(k + 1, 0, sign * x.magnitude());
        x = x - b;

        if(x.magnitude() > 1e-6){
            x.unit_mag();

            // H
            Matrix I(M, M); 
            Matrix xt = x.T();
            Matrix xxt = x * xt;
            xxt.scale(2.0f);
            Matrix H = I - xxt;

            // HAHT 
            Matrix HT = H.T();
            A = H * A * HT; 
        } else {
            break;
        }
        
    }

    return A;
}


// ............. 1D ...........................................................................................



Matrix Matrix::project(Matrix v){
    v.unit_mag();
    v.scale(dot(v));
    return v;
}




// flip argument? 
void Matrix::convolve_row(int m, Matrix& kernel){
    if(!(kernel.M == 1)){
        throw invalid_argument("");
    }  

    int half = (kernel.data.size() - 1) / 2;
    vector<float> temp = {};

    // Convolve 
    for(int center = 0; center < N; center++){
        float sum = 0.0f; 
        for(int kth = -half; kth <= half; kth++){
            int n = center + kth; 
            if(n >= 0 && n < N){
                sum += get(m, n) * kernel.data[half - kth];
            }
        }
        temp.push_back(sum);
    }

    // Set Row 
    for(int n = 0; n < N; n++){
        set(m, n, temp[n]);
    }
}

// flip argument?
void Matrix::convolve_col(int n, Matrix& kernel){
    if(!(kernel.N == 1)){
        throw invalid_argument("");
    }  

    int half = (kernel.data.size() - 1) / 2;
    vector<float> temp = {};

    for(int center = 0; center < M; center++){
        float sum = 0.0f; 
        for(int kth = -half; kth <= half; kth++){
            int m = center + kth; 
            if(m >= 0 && m < M){
                sum += get(m, n) * kernel.data[half - kth];
            }
        }
        temp.push_back(sum);
    }
   
    // Set Col 
    for(int m = 0; m < M; m++){
        set(m, n, temp[m]);
    }
}


// avoid making copy? 
void Matrix::scale(float scalar){
    for(int ith = 0; ith < data.size(); ith++){
        data[ith] *= scalar;
    }
}


void Matrix::elements_to_the(float power){
    for(int ith = 0; ith < data.size(); ith++){
        data[ith] = pow(data[ith], power);
    }
}

float Matrix::sum(){
    float total = 0.0f; 
    for(float value : data){
        total += value; 
    }
    return total;
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

// float Matrix::dot(Matrix& other){
//     return element_wise(other, '*').sum(); 
// }

// Claude version on trying to handle numerical stability?
// Corrected element-wise dot product with better numerical stability
// float Matrix::dot(Matrix& other){
//     if(!(M == other.M && N == other.N)){
//         cout << "Size Mismatch for dot product: "; 
//         cout << M << "x" << N << " & " << other.M << "x" << other.N << "\n";
//         throw invalid_argument("Matrix dimensions must match for element-wise dot product");
//     }
    
//     double total = 0.0; // Use double for better precision during accumulation
//     for(int ith = 0; ith < data.size(); ith++){
//         double product = static_cast<double>(data[ith]) * static_cast<double>(other.data[ith]);
//         total += product;
        
//         // Debug: Check for problematic values
//         if(!isfinite(product)) {
//             cout << "Non-finite product at index " << ith << ": " 
//                  << data[ith] << " * " << other.data[ith] << " = " << product << endl;
//         }
//     }
    
//     float result = static_cast<float>(total);
    
//     // Debug output for large results
//     if(abs(result) > 1000.0f) {
//         cout << "Warning: Large dot product result: " << result << endl;
        
//         // Print some statistics
//         float max_this = *max_element(data.begin(), data.end());
//         float min_this = *min_element(data.begin(), data.end());
//         float max_other = *max_element(other.data.begin(), other.data.end());
//         float min_other = *min_element(other.data.begin(), other.data.end());
        
//         cout << "This matrix range: [" << min_this << ", " << max_this << "]" << endl;
//         cout << "Other matrix range: [" << min_other << ", " << max_other << "]" << endl;
//     }
    
//     if(!isfinite(result)) {
//         throw runtime_error("Numerical overflow in element-wise dot product");
//     }
    
//     return result;
// }


float Matrix::dot(Matrix& other){
    // works for any sizes?... as long as same number of elemetns?....
    float sum = 0.0f;
    for(int i = 0; i < data.size(); i++){
        sum += other.data[i] * data[i];
    }
    return sum;
}

float Matrix::magnitude(){
    return sqrt(element_wise(*this, '*').sum());
}

// unit for differnt p norms in general ? and stuff...?
void Matrix::unit_mag(){
    scale(1.0f / magnitude());

}

void Matrix::unit_sum(){
    scale(1.0f / sum());
}

// unit_sum, unit_length, unit_mean etc. i think are good names for waht they do. 
// zero_mean? unit_std? 
// depending if it zeros or makes the quanityt a unit.


void Matrix::FFT(vector<complex<float>>& data){

    int N = data.size(); 

    if(N == 1){
        return; 
    }

    // Even & Odd
    vector<complex<float>> even; 
    vector<complex<float>> odd; 

    for(int ith = 0; ith < N; ith += 2){
        even.push_back(data[ith]); 
        odd.push_back(data[ith + 1]);
    }

    FFT(even); 
    FFT(odd);

    // Butterfly 
    float angle = -2 * M_PI / N; 
    complex<float> W(1, 0); 
    complex<float> W_N(cos(angle), sin(angle));

    for(int kth = 0; kth < N / 2; kth++){
        data[kth] = even[kth] + W * odd[kth]; 
        data[kth + N / 2] = even[kth] - W * odd[kth]; 
        W *= W_N; 
    }

}


void Matrix::FFT1D(){
    FFT(spectrum);
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

void Matrix::add_row(vector<float>& values){
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

void Matrix::add_column(vector<float>& values){
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

void Matrix::swap_row(int a, int b){
    for(int n = 0; n < N; n++){
        float past = get(b, n); 
        set(b, n, get(a, n)); 
        set(a, n, past);
    }
}

void Matrix::scale_row(int m, int scale){
    for(int n = 0; n < N; n++){
        set(m, n, get(m, n) * scale);
    }
}

void Matrix::row_minus(int m, Matrix row){

}

void Matrix::row_plus(int a, float scale, int b){
    for(int i = 0; i < N; i++){
        set(a, i, get(a, i) + scale * get(b, i));
    }
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



// ............................. Data stuff .......................................................................................................................
// returning the index? 
float Matrix::max(){
    vector<int> index = index_of_max(); 
    return get(index[0], index[1]);
}

// how about we return max, and it's index all in one?
vector<int> Matrix::index_of_max(){
    int row = -1; 
    int col = -1; 
    float max = numeric_limits<float>::lowest();

    for(int m = 0; m < M; m++){
        for(int n = 0; n < N; n++){
            float value = get(m, n); 
            if(value > max){
                max = value; 
                row = m; 
                col = n; 
            }
        }
    }

    vector<int> output = {row, col}; 
    return output; 
}

float Matrix::min(){
    float min = numeric_limits<float>::max();
    for(float value : data){
        if(value < min){
            min = value; 
        }
    }
    return min; 
}


void Matrix::range(float a, float b){
    float max = this->max(); 
    float min = this->min(); 

    if (max == min) {
        return;
    } else {
        float factor = (b - a) / (max - min); 
        vector<float> new_data; 
        for(int ith = 0; ith < data.size(); ith++){
            data[ith] = factor * (data[ith] - min) + a;
        }
    }    
}

void Matrix::range(float a, float b, float c, float d){
    if (b == a) {
        return;
    } else {
        float factor = (d - c) / (b - a); 
        vector<float> new_data; 
        for(int ith = 0; ith < data.size(); ith++){
            data[ith] = factor * (data[ith] - a) + c;
        }
    }    
}

void Matrix::randomize(float a, float b){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(a, b);
    for(int i = 0; i < data.size(); i++){
        data[i] = dis(gen); 
    }
}

// ensure it handles shrinking and expanding correctly. 

// make another resize method that just updates M & N only?.....
void Matrix::resize(int m, int n) {
        // vector<float> new_data(m * n, 0);


        // for (int row = 0; row < M; ++row) {
        //     for (int col = 0; col < N; ++col) {
        //         int ith = row * n + col; 
        //         if(ith >= 0 && ith < m * n){
        //             new_data[ith] = data[row * N + col];
        //         }
        //     }
        // }

        // M = m; 
        // N = n; 
        // data = new_data; 

    // claude version
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

        // if m == M && n == N then don't resize, if checking?



// // claude version
// void Matrix::resize(int m, int n) {
//     // Early return if dimensions are the same
//     if (m == M && n == N) {
//         return;
//     }
    
//     vector<float> new_data(m * n, 0);
    
//     // Copy existing data to new matrix
//     // Only copy up to the minimum dimensions to handle both shrinking and expanding
//     int rows_to_copy = std::min(M, m);
//     int cols_to_copy = std::min(N, n);
    
//     for (int row = 0; row < rows_to_copy; ++row) {
//         for (int col = 0; col < cols_to_copy; ++col) {
//             int old_idx = row * N + col;      // Index in original matrix
//             int new_idx = row * n + col;      // Index in new matrix
//             new_data[new_idx] = data[old_idx];
//         }
//     }
    
//     // Update dimensions and data
//     M = m;
//     N = n;
//     data = new_data;
// }



// expands into chunks of pixels w/ constant values w/ in these blocks. 
// each pixel is converted into a block of pixels w/ the same value
// should we handle stride length later?
Matrix Matrix::expand_pixels(int size){
    Matrix output(M * size, N * size, 0.0f);
    for(int m = 0; m < M; m++){
        for(int n = 0; n < N; n++){
            int y = m * size;  
            int x = n * size;  
            for(int k = 0; k < size; k++){
                for(int h = 0; h < size; h++){
                    output.set(y + k, x + h, get(m, n));
                }
            }
        }
    }
    return output; 
}

// every number can only be a multiple of the step size basically?

// by changing the step size to something larger perhaps we could simplfy the data & find more repeating values? 
// and allow for more compression? essentially it can make the image easier to work w/ data wise bassically
// imagine having to store 255 differnt values. to just 25 differnt values and still perserve a decent amount of information

// i guess its like integer multiplpes of the step size?.... im not sure to be honest...
// very useful function though......
void Matrix::step_change(float step){
    // so right now the step size can be really small e..g 5.0 -> 5.00001 
    // but what if you could change the step size to larger values 
    // e.g. 5 -> 6.  step size 1 
    // or even 5 -> 8. step size 3 
    // this could simplfy the amount of data that you have. and also 
    // it could create more repeated regions which can then be exploited w/ things like convolution. and perhaps compressing regeions? 
    

    for(int ith = 0; ith < data.size(); ith++){

        // the round part is basically finding the nearest integer multiple of the step size basically
        // choose ceil or floor instead. does always using ceil give a more interesting result?
        data[ith] = round(data[ith] / step) * step; 
    }
}


void Matrix::sort(){
    // implmeent differnt sorting algos later?
    std::sort(data.begin(), data.end());
}


void Matrix::gamma_correction(float gamma) {
    float a = min(); 
    float b = max();
    range(0.0f, 1.0f);
    for(int ith = 0; ith < data.size(); ith++){
        data[ith] = pow(data[ith], gamma);
    }
    range(a, b);
}


/** @param k if >= k -> 1 */
void Matrix::threshold(float k){
    for(int ith = 0; ith < data.size(); ith++){
        if(data[ith] >= k){
            data[ith] = 1.0f;
        } else {
            data[ith] = 0.0f;
        }
    }
}

// if u add an inverted image w/ it's univernted image, im pretty sure it would go to a constant value or something. maybe even zero
void Matrix::invert(){
    int a = min(); 
    int b = max(); 
    scale(-1.0f); 
    range(a, b);
}


float Matrix::mean(){
    float sum = 0.0f; 
    for(float value : data){
        sum += value; 
    }
    return sum / data.size(); 
}

float Matrix::std(){
    float mu = mean(); 
    float sum = 0.0f; 
    for(float value : data){
        sum += pow(value - mu, 2.0f);
    }
    sum /= data.size(); // Variance
    return sqrt(sum);
}


void Matrix::zero_mean(){
    // store mean in feild to avoid recomputation?
    float mu = mean();
    for(int ith = 0; ith < data.size(); ith++){
        data[ith] -= mu; 
    }
}

// does this make the std one?
void Matrix::unit_std(){
    float sigma = std(); 
    for(int ith = 0; ith < data.size(); ith++){
        data[ith] /= sigma; 
    }
}


void Matrix::absolute(){
    for(int i = 0; i < data.size(); i++){
        data[i] = abs(data.at(i));
    }
}


// ................. miscellaneous ............................................................................................................................................
Mat Matrix::to_mat() {
    Mat mat(M, N, CV_32F, data.data());
    mat.convertTo(mat, CV_8U);
    return mat;
}

Matrix Matrix::gaussian_kernel(int size, float deviation){
    Matrix output(size, size, 0);

    // is the A even nessecary here? since we are already normalizing w/ diving by the sum
    float A = 2 * M_PI * pow(deviation, 2);  // The normalization factor
    float sigma_squared = pow(deviation, 2); // This is sigma^2
    int center = size / 2; 
    
    // Calculate kernel values
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            float arg = pow(x - center, 2) + pow(y - center, 2);
            output.set(x, y, exp(-0.5f * arg / sigma_squared) / A);
        }
    }

    output.scale(1.0f / output.sum());
    return output; 
}


vector<float> Matrix::get_reals(vector<complex<float>>& data){
    vector<float> output = {}; 
    for(complex<float> z : data){
        output.push_back(z.real());
    }
    return output; 
}

vector<float> Matrix::get_imaginaries(vector<complex<float>>& data){
    vector<float> output = {}; 
    for(complex<float> z : data){
        output.push_back(z.imag());
    }
    return output; 
}

vector<complex<float>> Matrix::merge_real_and_imag(vector<float>& real, vector<float>& imag){
    vector<complex<float>> output = {}; 
    for(int ith = 0; ith < real.size(); ith++){
        output.push_back(complex<float>(real[ith], imag[ith]));
    }
    return output; 
}

Matrix Matrix::copy(){
    return Matrix (M, N, this->data); 
}

Matrix* Matrix::pointer_copy(){
    return new Matrix (M, N, this->data); 
}






// void Matrix::FFT2D(){

//     Matrix real_matrix(0, N, 0);
//     Matrix imaginary_matrix(0, N, 0);

//     Matrix* real_spectrum = new Matrix(M, 0, 0);
//     Matrix* imag_spectrum = new Matrix(M, 0, 0);

//     // FFT Rows 
//     for(int m = 0; m < M; m++){ 
//         vector<complex<float>> fft = FFT_row(m);
//         vector<float> reals = get_reals(fft);
//         vector<float> imaginaries = get_imaginaries(fft);
//         real_matrix.add_row(reals);
//         imaginary_matrix.add_row(imaginaries);
//     }

//     for(int n = 0; n < N; n++){
//         vector<float> reals = real_matrix.get_column(n).data;
//         vector<float> imaginaries = imaginary_matrix.get_column(n).data;
//         vector<complex<float>> column = merge_real_and_imag(reals, imaginaries); 
//         FFT(column); 
//         reals = get_reals(column); 
//         imaginaries = get_imaginaries(column); 
//         real_spectrum->add_column(reals);  
//         imag_spectrum->add_column(imaginaries);
//     }

//     this->real_spectrum = real_spectrum;
//     this->imag_spectrum = imag_spectrum;


// }

// is convoution fliping the signal right?







void Matrix::normalized_correlate(Matrix& kernel) {
    // Output size for valid correlation (no padding)
    int out_M = M - kernel.M + 1;
    int out_N = N - kernel.N + 1;
    
    if(out_M <= 0 || out_N <= 0) {
        throw invalid_argument("Kernel is larger than image");
    }
    
    vector<float> temp(out_M * out_N, 0);
    
    // Pre-calculate kernel statistics
    float kernel_sum = 0.0f;
    float kernel_sum_sq = 0.0f;
    int kernel_size = kernel.M * kernel.N;
    
    for(int k = 0; k < kernel.M; k++) {
        for(int h = 0; h < kernel.N; h++) {
            float val = kernel.get(k, h);
            kernel_sum += val;
            kernel_sum_sq += val * val;
        }
    }
    
    float kernel_mean = kernel_sum / kernel_size;
    float kernel_var = kernel_sum_sq / kernel_size - kernel_mean * kernel_mean;
    float kernel_std = sqrt(kernel_var);
    
    // For each position in output
    for(int m = 0; m < out_M; m++) {
        for(int n = 0; n < out_N; n++) {
            
            // Calculate patch statistics
            float patch_sum = 0.0f;
            float patch_sum_sq = 0.0f;
            
            for(int k = 0; k < kernel.M; k++) {
                for(int h = 0; h < kernel.N; h++) {
                    float val = get(m + k, n + h);
                    patch_sum += val;
                    patch_sum_sq += val * val;
                }
            }
            
            float patch_mean = patch_sum / kernel_size;
            float patch_var = patch_sum_sq / kernel_size - patch_mean * patch_mean;
            float patch_std = sqrt(patch_var);
            
            // Calculate normalized correlation
            float correlation = 0.0f;
            
            if(patch_std > 1e-6 && kernel_std > 1e-6) {  // Avoid division by zero
                for(int k = 0; k < kernel.M; k++) {
                    for(int h = 0; h < kernel.N; h++) {
                        float patch_val = get(m + k, n + h);
                        float kernel_val = kernel.get(k, h);
                        
                        correlation += (patch_val - patch_mean) * (kernel_val - kernel_mean);
                    }
                }
                correlation /= (kernel_size * patch_std * kernel_std);
            }
            
            temp[out_N * m + n] = correlation;
        }
    }
    
    data = temp;
    M = out_M;
    N = out_N;
}


// this has some copmutatianly efficent things if im not mistaken
void Matrix::zero_mean_unit_std(){
    float mean_val = 0.0f;
    float sum_sq = 0.0f;

    for(float val : data){
        mean_val += val;
        sum_sq += val * val;
    }

    mean_val /= data.size();
    float variance = sum_sq / data.size() - mean_val * mean_val;
    float stddev = sqrt(variance);

    if(stddev < 1e-6){
        stddev = 1.0f; // avoid division by zero, treat as flat image
    }

    for(float& val : data){
        val = (val - mean_val) / stddev;
    }
}


// void Matrix::print(){
//     for(int m = 0; m < M; m++){
//         for(int n = 0; n < N; n++){
//             cout << get(m, n) << " ";
//         }
//         cout << "\n";
//     }
// }

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

    // add a cout << "\n" here for conveince?....
}




void Matrix::load(string path){
    ifstream in(path);
    string text = string((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    string number = "";

    int m; 
    int n; 
    vector<float> imported_data = {}; 

    // Read Data
    int count = 0; 
    for(char character : text){
        if(character == ','){
            if(count == 0){
                m = stoi(number); 
                number = "";
                count++;
            } else if(count == 1){
                n = stoi(number); 
                number = "";
                count++;
            } else {
                imported_data.push_back(stof(number));
                number = "";
            }
        } else {
            number += character;
        }
    }

    data = imported_data; 
    M = m; 
    N = n;
}


void Matrix::save(string path){
    string csv; 
    csv += to_string(M) + "," + to_string(N) + ","; 
    for(int ith = 0; ith < data.size(); ith++){
        csv += to_string(data[ith]) + ",";
    }
    ofstream out(path); 
    if (out.is_open()) {
        out << csv; 
        out.close(); 
    } else {
        std::cerr << "Failed to open file for writing.\n";
    }
}


void Matrix::save_as_image(string path, bool grayscale){
    Matrix output = *this;
    output.range(0.0f, 255.0f);
    if(grayscale){
        imwrite(path, output.to_mat());
    }
}




// histogram methods?

void Matrix::histogram_equalization(){
    // PDF 
    Matrix pdf(1, 256);
    for(float pixel : data){
        pdf.data[round(pixel)]++;
    }
    pdf.unit_sum();

    // CDF 
    Matrix cdf(1, 256); 
    float sum = 0.0f;
    for(int ith = 0; ith < pdf.N; ith++){
        sum += pdf.get(0, ith);
        cdf.set(0, ith, sum);
    }
    cdf.scale(255.0f);

    // Histogram Equalization. 
    for(int ith = 0; ith < data.size(); ith++){
        data[ith] = cdf.get(0, round(data[ith])); 
    }
}