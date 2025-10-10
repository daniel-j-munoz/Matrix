
// void Matrix::convolve(Matrix& kernel, bool flip){
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

// void Matrix::convolve_validd(Matrix& kernel, int new_m, int new_n, bool flip){
//     int F = flip ? -1 : 1;
//     int halfY = kernel.M / 2;
//     int halfX = kernel.N / 2;

//     // Starting positions to center the smaller output inside the full convolved result
//     int offsetY = (M - new_m) / 2;
//     int offsetX = (N - new_n) / 2;

//     vector<float> temp(new_m * new_n, 0);

//     for(int m = 0; m < new_m; m++){
//         for(int n = 0; n < new_n; n++){
//             float sum = 0.0f;
//             int centerY = m + offsetY;
//             int centerX = n + offsetX;

//             for(int k = -halfY; k <= halfY; k++){
//                 for(int h = -halfX; h <= halfX; h++){
//                     int y = centerY + k;
//                     int x = centerX + h;
//                     if (y >= 0 && y < M && x >= 0 && x < N){
//                         sum += get(y, x) * kernel.get(halfY - F * k, halfX - F * h);
//                     }
//                 }
//             }
//             temp[new_n * m + n] = sum;
//         }
//     }

//     // Set new size and data
//     this->M = new_m;
//     this->N = new_n;
//     this->data = temp;

// }






// // does this work?
// void Matrix::convolve_valid(Matrix& kernel, bool flip) {
//     int half = kernel.M / 2;
//     int out_M = M - kernel.M + 1;
//     int out_N = N - kernel.N + 1;

//     vector<float> temp(out_M * out_N, 0);

//     for (int m = 0; m < out_M; m++) {
//         for (int n = 0; n < out_N; n++) {
//             float sum = 0.0f;

//             for (int k = 0; k < kernel.M; k++) {
//                 for (int h = 0; h < kernel.N; h++) {
//                     int y = m + k;
//                     int x = n + h;

//                     int kk = flip ? (kernel.M - 1 - k) : k;
//                     int hh = flip ? (kernel.N - 1 - h) : h;

//                     sum += get(y, x) * kernel.get(kk, hh);
//                 }
//             }

//             temp[out_N * m + n] = sum;
//         }
//     }

//     // Update dimensions and data
//     M = out_M;
//     N = out_N;
//     data = temp;
// }

// void Matrix::convolve_me(Matrix& kernel, bool flip) {
//     int half = kernel.M / 2;
//     int f = flip ? -1 : 1;
//     vector<float> temp = data; // Start with original data
    
//     // Only convolve the valid region (where kernel fits completely)
//     for(int m = half; m < M - half; m++) {
//         for(int n = half; n < N - half; n++) {
//             float sum = 0.0f;
//             for(int k = -half; k <= half; k++) {
//                 for(int h = -half; h <= half; h++) {
//                     sum += get(m - k * f, n - h * f) * kernel.get(k + half, h + half);
//                 }
//             }
//             temp[m * N + n] = sum;
//         }
//     }
    
//     data = temp;
// }















// void Matrix::normalized_correlate(Matrix& kernel) {
//     // Output size for valid correlation (no padding)
//     int out_M = M - kernel.M + 1;
//     int out_N = N - kernel.N + 1;
    
//     if(out_M <= 0 || out_N <= 0) {
//         throw invalid_argument("Kernel is larger than image");
//     }
    
//     vector<float> temp(out_M * out_N, 0);
    
//     // Pre-calculate kernel statistics
//     float kernel_sum = 0.0f;
//     float kernel_sum_sq = 0.0f;
//     int kernel_size = kernel.M * kernel.N;
    
//     for(int k = 0; k < kernel.M; k++) {
//         for(int h = 0; h < kernel.N; h++) {
//             float val = kernel.get(k, h);
//             kernel_sum += val;
//             kernel_sum_sq += val * val;
//         }
//     }
    
//     float kernel_mean = kernel_sum / kernel_size;
//     float kernel_var = kernel_sum_sq / kernel_size - kernel_mean * kernel_mean;
//     float kernel_std = sqrt(kernel_var);
    
//     // For each position in output
//     for(int m = 0; m < out_M; m++) {
//         for(int n = 0; n < out_N; n++) {
            
//             // Calculate patch statistics
//             float patch_sum = 0.0f;
//             float patch_sum_sq = 0.0f;
            
//             for(int k = 0; k < kernel.M; k++) {
//                 for(int h = 0; h < kernel.N; h++) {
//                     float val = get(m + k, n + h);
//                     patch_sum += val;
//                     patch_sum_sq += val * val;
//                 }
//             }
            
//             float patch_mean = patch_sum / kernel_size;
//             float patch_var = patch_sum_sq / kernel_size - patch_mean * patch_mean;
//             float patch_std = sqrt(patch_var);
            
//             // Calculate normalized correlation
//             float correlation = 0.0f;
            
//             if(patch_std > 1e-6 && kernel_std > 1e-6) {  // Avoid division by zero
//                 for(int k = 0; k < kernel.M; k++) {
//                     for(int h = 0; h < kernel.N; h++) {
//                         float patch_val = get(m + k, n + h);
//                         float kernel_val = kernel.get(k, h);
                        
//                         correlation += (patch_val - patch_mean) * (kernel_val - kernel_mean);
//                     }
//                 }
//                 correlation /= (kernel_size * patch_std * kernel_std);
//             }
            
//             temp[out_N * m + n] = correlation;
//         }
//     }
    
//     data = temp;
//     M = out_M;
//     N = out_N;
// }













//  // what if you just return a vector of both? a vector w/ mask, shrinked and non shrinked.
//     // or what if you can type it w/ string e.g. "Mask, Shrink" 
//     // and it returns a mask and shrink in that order in a vector

// void Matrix::max_pool(int size, bool mask) {
//     int step = size; 
//     int new_M = (M - size) / step + 1; 
//     int new_N = (N - size) / step + 1; 
//     vector<float> mask_data(M * N, 0.0f); 
//     vector<float> new_data(new_M * new_N, 0.0f); 

//     // Center
//     for(int m = 0; m < new_M; m ++){
//         for(int n = 0; n < new_N; n++){

//             // Starting point
//             int y = step * m; 
//             int x = step * n; 

//             // Max Pool
//             float max = numeric_limits<float>::lowest(); 
//             // int row_max, col_max; // i think having unitialized values was causing bugs ***************************************************************
//             int row_max = y, col_max = x;  // Initialize to starting position 
//             for(int k = 0; k < size; k++){
//                 for(int h = 0; h < size; h++){
//                     int row = y + k; 
//                     int col = x + h; 


//                     if(get(row, col) > max){
//                         max = get(row, col); 
//                         row_max = row; 
//                         col_max = col;
//                     }
//                 }
//             }

//             if(mask){
//                 mask_data[N * row_max + col_max] = 1;
//             } else {
//                 new_data[new_N * m + n] = max;
//             }
//         }
//     }

//     if(mask){
//         data = mask_data; 
//     } else {
//         data = new_data; 
//         M = new_M; 
//         N = new_N;
//     }

    
// }


// // so what if instead of a mean. we used a guassian? 
// // so sort of weighted average basically
// void Matrix::mean_pool(int size) {
//     int stride = size; 

//     // essentially measuring how many boxes you can fit in each direction given your stride and size lenght.
//     int new_M = (M - size) / stride + 1; 
//     int new_N = (N - size) / stride + 1; 
//     vector<float> temp(new_M * new_N, 0.0f); 

//     // Center
//     for(int m = 0; m < new_M; m ++){
//         for(int n = 0; n < new_N; n++){

//             // Starting point
//             int y = stride * m; 
//             int x = stride * n; 

//             // Max Pool
//             float sum = 0.0f;
//             for(int k = 0; k < size; k++){
//                 for(int h = 0; h < size; h++){
//                     sum += get(y + k, x + h);
                    
//                 }
//             } 
//             temp[new_N * m + n] = sum / (size * size);
//         }
//     }

//     data = temp; 
//     M = new_M; 
//     N = new_N; 
// }














// // conv by seperability 
// // how can we make these multiplicatinos and additions more efficient? 
// // more effective? 

// void Matrix::convolve_seperable(Matrix& A){

//     // int size = A.data.size(); 
//     // int half = (size - 1) / 2; 
//     // Matrix horz(1, size, 0.0f); 
//     // Matrix vert(size, 1, 0.0f);


//     // Matrix A_T = A.T();
//     // A.product(A_T);



//     // // Horzitonal Convolution
//     // for(int m = 0; m < M; m++){
//     //     convolve_row(m, horz); 
//     // }

//     // // Vertical Convolution on intermediate image
//     // for(int n = 0; n < N; n++){
//     //     convolve_col(n, vert);
//     // }

// }


















// // of course we could probably use SVD for the kernel. 
// // but then we have to rely on numerical methods and stuff. 
// // but the guassian can be implemented in a more straightforward_pass manner w/ out having to do the SVD. 
// // we can find the vert and horz of guassian w/ out having to use SVD

// // but guassian blur in image instead or something? 
// // since ti's more of an image method than matrix method?

// // is 'A' nessecary? 
// // ask gpt if it can be writen better?
// void Matrix::guassian_blur(int size, float sigma){
//     Matrix output(size, size, 0);

//     float sigma_squared = pow(sigma, 2.0f); 
//     float a = pow(2.0f * M_PI * sigma_squared, -1.0f);
//     float A = pow(2.0f * M_PI * sigma_squared, -0.5f);
//     int center = (size - 1) / 2; 
    
//     Matrix horz(1, size, 0.0f); 
//     Matrix vert(size, 1, 0.0f);

//     float sum = 0.0f;
//     for (int x = 0; x < size; x++) {
//         for (int y = 0; y < size; y++) {
//             float input = pow(x - center, 2.0f) + pow(y - center, 2.0f);
//             sum += a * exp(-0.5f / sigma_squared * input);
//         }
//     }

//     // Horizontal & Vertical
//     for (int ith = 0; ith < size; ith++) {
//         float input = pow(ith - center, 2.0f);
//         float value = A * exp(-0.5f / sigma_squared * input);
//         horz.set(0, ith, value / sum); 
//         vert.set(ith, 0, value); 
//     }

//     // Horzitonal Convolution
//     for(int m = 0; m < M; m++){
//         convolve_row(m, horz); 
//     }

//     // Vertical Convolution on Intermediate Image
//     for(int n = 0; n < N; n++){
//         convolve_col(n, vert);
//     }
// }














// void Matrix::sep_conv_sobel_x(){
//     vector<float> data;
//     data = {-1, 0, 1};
//     Matrix horz(1, 3, data); 
//     data = {1, 2, 1};
//     Matrix vert(3, 1, data);
//     horz.scale(1.0f / 8.0f);  // scale or dont' scale?

//     // create a sep conv method? takes in vert and horz components?
//     // then create a get component for popular kernels like sobel and guassian
//     // seperating a general kernel would require something like SVD i think

//     // Horzitonal Convolution
//     for(int m = 0; m < M; m++){
//         convolve_row(m, horz); 
//     }

//     // Vertical Convolution on Intermediate Image
//     for(int n = 0; n < N; n++){
//         convolve_col(n, vert);
//     }
// }

// void Matrix::sep_conv_sobel_y(){
//     vector<float> data;
//     data = {1, 2, 1};
//     Matrix horz(1, 3, data); 
//     data = {-1, 0, 1};
//     Matrix vert(3, 1, data);
//     horz.scale(1.0f / 8.0f); // scale or don't scale?

//     // Horzitonal Convolution
//     for(int m = 0; m < M; m++){
//         convolve_row(m, horz); 
//     }

//     // Vertical Convolution on Intermediate Image
//     for(int n = 0; n < N; n++){
//         convolve_col(n, vert);
//     }
// }




// // yeah perhaps handle general conv by sep. and instead generater vector of svd for stuff like guass blur and stuff. 
// // then input for methods that work w/ general components ands tuff... just writing what comes to head and stuff...




// /**
//  * @param a horizontal kernel
//  * @param b vertical kernel
//  */
// void Matrix::convolve_sep(Matrix& a, Matrix& b){
//     // Horzitonal Convolution
//     for(int m = 0; m < M; m++){
//         convolve_row(m, a); 
//     }

//     // Vertical Convolution on Intermediate Image
//     for(int n = 0; n < N; n++){
//         convolve_col(n, b);
//     }
// }








// void Matrix::FFT2D(){
//     // Pre-allocate result matrices to avoid repeated add_column operations
//     real_spectrum = new Matrix(M, N, 0.0f);
//     imag_spectrum = new Matrix(M, N, 0.0f);
    
//     // Temporary storage for row processing
//     vector<complex<float>> row_data(N);
    
//     // FFT on rows - process in-place to avoid copying
//     for(int m = 0; m < M; m++){
//         // Copy row data directly without creating Matrix object
//         for(int n = 0; n < N; n++){
//             row_data[n] = complex<float>(get(m, n), 0.0f);
//         }
        
//         // Perform FFT on row
//         FFT(row_data);
        
//         // Store results directly in pre-allocated matrices
//         for(int n = 0; n < N; n++){
//             real_spectrum->set(m, n, row_data[n].real());
//             imag_spectrum->set(m, n, row_data[n].imag());
//         }
//     }
    
//     // Temporary storage for column processing
//     vector<complex<float>> col_data(M);
    
//     // FFT on columns - process in-place
//     for(int n = 0; n < N; n++){
//         // Extract column data directly
//         for(int m = 0; m < M; m++){
//             col_data[m] = complex<float>(real_spectrum->get(m, n), imag_spectrum->get(m, n));
//         }
        
//         // Perform FFT on column
//         FFT(col_data);
        
//         // Store results back directly
//         for(int m = 0; m < M; m++){
//             real_spectrum->set(m, n, col_data[m].real());
//             imag_spectrum->set(m, n, col_data[m].imag());
//         }
//     }
// }











// // flip argument? 
// void Matrix::convolve_row(int m, Matrix& kernel){
//     if(!(kernel.M == 1)){
//         throw invalid_argument("");
//     }  

//     int half = (kernel.data.size() - 1) / 2;
//     vector<float> temp = {};

//     // Convolve 
//     for(int center = 0; center < N; center++){
//         float sum = 0.0f; 
//         for(int kth = -half; kth <= half; kth++){
//             int n = center + kth; 
//             if(n >= 0 && n < N){
//                 sum += get(m, n) * kernel.data[half - kth];
//             }
//         }
//         temp.push_back(sum);
//     }

//     // Set Row 
//     for(int n = 0; n < N; n++){
//         set(m, n, temp[n]);
//     }
// }

// // flip argument?
// void Matrix::convolve_col(int n, Matrix& kernel){
//     if(!(kernel.N == 1)){
//         throw invalid_argument("");
//     }  

//     int half = (kernel.data.size() - 1) / 2;
//     vector<float> temp = {};

//     for(int center = 0; center < M; center++){
//         float sum = 0.0f; 
//         for(int kth = -half; kth <= half; kth++){
//             int m = center + kth; 
//             if(m >= 0 && m < M){
//                 sum += get(m, n) * kernel.data[half - kth];
//             }
//         }
//         temp.push_back(sum);
//     }
   
//     // Set Col 
//     for(int m = 0; m < M; m++){
//         set(m, n, temp[m]);
//     }
// }













// // 1D....

// void Matrix::FFT(vector<complex<float>>& data){

//     int N = data.size(); 

//     if(N == 1){
//         return; 
//     }

//     // Even & Odd
//     vector<complex<float>> even; 
//     vector<complex<float>> odd; 

//     for(int ith = 0; ith < N; ith += 2){
//         even.push_back(data[ith]); 
//         odd.push_back(data[ith + 1]);
//     }

//     FFT(even); 
//     FFT(odd);

//     // Butterfly 
//     float angle = -2 * M_PI / N; 
//     complex<float> W(1, 0); 
//     complex<float> W_N(cos(angle), sin(angle));

//     for(int kth = 0; kth < N / 2; kth++){
//         data[kth] = even[kth] + W * odd[kth]; 
//         data[kth + N / 2] = even[kth] - W * odd[kth]; 
//         W *= W_N; 
//     }

// }


// void Matrix::FFT1D(){
//     FFT(spectrum);
// }



// vector<float> Matrix::get_reals(vector<complex<float>>& data){
//     vector<float> output = {}; 
//     for(complex<float> z : data){
//         output.push_back(z.real());
//     }
//     return output; 
// }

// vector<float> Matrix::get_imaginaries(vector<complex<float>>& data){
//     vector<float> output = {}; 
//     for(complex<float> z : data){
//         output.push_back(z.imag());
//     }
//     return output; 
// }

// vector<complex<float>> Matrix::merge_real_and_imag(vector<float>& real, vector<float>& imag){
//     vector<complex<float>> output = {}; 
//     for(int ith = 0; ith < real.size(); ith++){
//         output.push_back(complex<float>(real[ith], imag[ith]));
//     }
//     return output; 
// }



// Matrix Matrix::gaussian_kernel(int size, float deviation){
//     Matrix output(size, size, 0);

//     // is the A even nessecary here? since we are already normalizing w/ diving by the sum
//     float A = 2 * M_PI * pow(deviation, 2);  // The normalization factor
//     float sigma_squared = pow(deviation, 2); // This is sigma^2
//     int center = size / 2; 
    
//     // Calculate kernel values
//     for (int x = 0; x < size; x++) {
//         for (int y = 0; y < size; y++) {
//             float arg = pow(x - center, 2) + pow(y - center, 2);
//             output.set(x, y, exp(-0.5f * arg / sigma_squared) / A);
//         }
//     }

//     output.scale(1.0f / output.sum());
//     return output; 
// }