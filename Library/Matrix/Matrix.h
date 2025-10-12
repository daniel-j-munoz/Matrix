#include <opencv2/opencv.hpp>
#include <iostream> 
#include <vector> 
using namespace std;
using namespace cv; 


#pragma once
class Matrix {
    public: 



        // To be used tags .....
        // looking at properties can
        // be used to do more efficent computat and stuff...
        // e.g. inverse method etc....
        
        // bool orthogonal = false;
        // bool permutation = false;
        // bool row = false;
        // bool column = false;
        // bool singular = false;
        // bool positive_definite = false;
        // bool negative_definite = false;
        // bool identity = false;
        // bool zero = false;
        // bool sparse = false;
        // bool square = false;
        // bool involutory = false;
        // bool symmetric = false; 
        // bool hermitian = false;
        // bool diagonal = false;
        // bool tridiagonal = false;
        // bool right_triangle = false;
        // bool left_triangle = false;
        // bool upper_hessenberg = false;
        // bool complex = false;

        void tag();



        int M; 
        int N; 
        vector<float> data; 
        Matrix(int M, int N, vector<float> data); 
        Matrix(int M, int N, float value); 
        Matrix(int M, int N); 

        // ........................ Matrix .........................................................
        Matrix T(); 
        Matrix invert(); // copy or void? 
        float DET(); 
        float TRIDET(); // determinant of triangular matrix
        float count_swaps();
        void square(int size); 
        void resize(int m, int n);

        // ............... Row & Col ................................................
        float get(int m, int n); 
        void set(int m, int n, float value);
        Matrix get_row(int index); 
        Matrix get_column(int index); 
        void add_row(vector<float>& values);



        void add_column(vector<float>& values);
        void add_column(Matrix column);
        void add_matrix(Matrix A);
        
        /**
         * Region of Interest
         * Inclusive Bounds
         * Can wrap around matrix
         * submatrix subspace
         * general roi?
         */
        Matrix* ROI(int row, int col, int next_row, int next_col);

        // ........................ Vector .........................................................
        Matrix project(Matrix v);


        // ....... Arithemtic ...................................................
        Matrix element_wise(Matrix& other, char operation);
        Matrix operator*(float scale);
        Matrix operator*=(float scale);
        void scale(float scalar); // keep scale as well... i think... both are helpful i belive...
        Matrix operator*(Matrix& other); // Mat Mult
        Matrix operator*=(Matrix& other); 
        Matrix operator+(Matrix& other);
        Matrix operator+=(Matrix& other);
        Matrix operator-(Matrix& other);
        Matrix operator-=(Matrix& other);
        float dot(Matrix& other);  


        // Setting and stuff .............................................
        void to_row_vector(); 
        void to_column_vector();
        void reshape(int m, int n);
        
        float L2(); 
        float LI();
        float L(float p);


        Matrix copy(); 
        /**
         * print to x many decimal places
         */
        void print(int x);
};