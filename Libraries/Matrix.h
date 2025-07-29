#include <opencv2/opencv.hpp>
#include <iostream> 
#include <vector> 
using namespace std;
using namespace cv; 

/**
 * Row Major Order
 * Matrix & Vector sections are not strictly for vectors and matricies. 
 * e.g. matrix can use vector section methods. and your col/row vectors can use vector secontion methods as well
 */

#pragma once
class Matrix {
    public: 

        // float mean; // ???
        // float std; // ???

        int M; 
        int N; 
        vector<float> data; 
        vector<complex<float>> spectrum; 

        Matrix* real_spectrum = nullptr; 
        Matrix* imag_spectrum = nullptr; 

        /** @param data row major order */
        Matrix(int M, int N, vector<float>& data); 
        /** @param value init w/ value */
        Matrix(int M, int N, float value); 
        /**Identity Matrix */
        Matrix(int M, int N); 

        // ........................ Matrix .........................................................
        void guassian_blur(int size, float sigma); 
        void sep_conv_sobel_x(); 
        void sep_conv_sobel_y(); 

        // ........... FFT & Convolution .................................
        void FFT2D();
        void convolve(Matrix& kernel, bool flip);
        void convolve_me(Matrix& kernel, bool flip);  
        void convolve_valid(Matrix& kernel, bool flip); // stride length, padding parameters?
        void convolve_validd(Matrix& kernel, int m, int n, bool flip);
        void convolve_seperable(Matrix& kernel);

        // ................. Pooling ...................................................
        // max_pool and avg pool in 1D as well? 
        // have it take in stride lengths as well? 
        void max_pool(int size, bool mask);
        void mean_pool(int size); 
        void median_pool(int size); 
        void square(int size); // turn into square matrix. use resize method?
        // guassian pooling? 
        // l2 pooling?

        Matrix expand_pixels(int size); 

        // ........ Linear Algebra ...............
        // void product(Matrix* other); 

   

        void rref(); 
        void transpose(); 
        float determinant(); 
        // inverse

        // Resize Methods? 
        void resize(int m, int n);

        // ............... Row & Col ................................................
        float get(int m, int n); 
        void set(int m, int n, float value);

        Matrix get_row(int index); 
        void add_row(vector<float>& values);
        void swap_row(int a, int b);
        void scale_row(int m, int scale);

        Matrix get_column(int index); 
        void add_column(vector<float>& values);
        
        /**
         * Region of Interest
         * Inclusive Bounds
         * Can wrap around matrix
         * submatrix subspace
         * general roi?
         */
        Matrix* ROI(int row, int col, int next_row, int next_col);

        // ........................ Vector .........................................................

        // ........... FFT & Convultion .....................................
        static void FFT(vector<complex<float>>& data);
        void FFT1D();
        void convolve_row(int m, Matrix& kernel);
        void convolve_col(int n, Matrix& kernel);
        // instead of FFT1D ?
        vector<complex<float>> FFT_row(int m); 
        vector<complex<float>> FFT_col(int n); 




             // matrix multiplciation
        Matrix operator*(Matrix& other); 
        Matrix operator*=(Matrix& other); // compound operator?

        // ....... Arithemtic ...................................................


        Matrix element_wise(Matrix& other, char operation);
 
        // Plus and minus and compound operators
        Matrix operator+(Matrix& other);
        Matrix operator+=(Matrix& other);
        Matrix operator-(Matrix& other);
        Matrix operator-=(Matrix& other);


        // Setting and stuff .............................................
        void scale(float scalar);
        /** pow function on each element */
        void elements_to_the(float power); 
        void invert(); 

        /** inclusive bounds */
        void randomize(float a, float b);  

        /** inclusive bounds */ 
        void range(float a, float b); 

        void step_change(float step);

        void gamma_correction(float gamma);
        void threshold(float k);
        
        void sort(); 
        void to_row_vector(); 
        void to_column_vector();
        void reshape(int m, int n);
        
        float sum(); 
        float magnitude();
        float dot(Matrix& other); 

        vector<int> index_of_max(); 
        float max(); 
        float min(); 

        float mean(); 
        float std(); 
        void zero_mean(); 
        void unit_std();
        void unit_mag(); 
        void unit_sum(); 


        Matrix copy(); 
        Matrix* pointer_copy();


        /**
         * print to x many decimal places
         */
        void print(int x);


        /** load text csv files */
        void load(string path);  
        void save(string path);
        void save_as_image(string path, bool grayscale);


        Mat to_mat(); 
        static Matrix gaussian_kernel(int size, float deviation); 
        static vector<float> get_reals(vector<complex<float>>& data);
        static vector<float> get_imaginaries(vector<complex<float>>& data);
        static vector<complex<float>> merge_real_and_imag(vector<float>& real, vector<float>& imag);
        void normalized_correlate(Matrix& kernel);
        void zero_mean_unit_std();



        void histogram_equalization(); 
};
