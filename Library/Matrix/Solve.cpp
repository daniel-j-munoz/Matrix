#include "Solve.h"
#include "Factor.h"
#include "Guass.h"

/**
 * assumes A is mxm
 */
Matrix Solve::LU(Matrix A, Matrix B){
    vector<Matrix> LU = Factor::LU(A);
    B = LU[0].T() * B;
    Matrix Y = foward(LU[1], B);
    return backward(LU[2], Y);
}

// pivoted cholesky? for non positive definite?
/**
 * for Hermitatian & Positive Definite
 * assumes A mxm
 */
Matrix Solve::cholesky(Matrix A, Matrix B){
    vector<Matrix> LLT = Factor::cholesky(A);
    Matrix Y = foward(LLT[0], B);
    return backward(LLT[1], Y);
}

/**
 * @param A lower left triangular mxm
 */
Matrix Solve::foward(Matrix A, Matrix B){
    Matrix X(B.M, B.N, 0.0f);

    for(int i = 0; i < B.N; i++){
        for(int j = 0; j < B.M; j++){
            float x = B.get(j, i);
            for(int k = 0; k < j; k++){
                x -= A.get(j, k) * X.get(k, i);
            }
            x /= A.get(j, j);
            X.set(j, i, x);
        }
    }
    return X;
}

/**
 * @param A Upper Right Triangular mxm 
 */
Matrix Solve::backward(Matrix A, Matrix B){
    Matrix X(B.M, B.N, 0.0f);

    for(int i = 0; i < B.N; i++){
        for(int j = B.M - 1; j >= 0; j--){
            float x = B.get(j, i); 
            for(int k = j + 1; k < B.M; k++){
                x -= A.get(j, k) * X.get(k, i);
            }
            x /= A.get(j, j);
            X.set(j, i, x);
        }
    }
    
    return X;
}

/**
 * @param A mxm for now
 * @param B mxn
 */
vector<Matrix> Solve::RREF(Matrix A, Matrix B){
    float e = 1e-9f;

    for(int i = 0; i < A.M; i++){
        // pivot
        float max = 0.0f;
        int index = i;
        for(int j = i; j < A.M; j++){
            float value = abs(A.get(j, i));
            if(value > max){
                max = value;
                index = j;
            }
        }

        if(max > e){
            // swap 
            Guass::swap_row(i, index, &A);
            Guass::swap_row(i, index, &B);

            // scale
            float scale = 1.0f / A.get(i, i);
            Guass::scale_row(i, scale, &A);
            Guass::scale_row(i, scale, &B);

            // zero
            for(int j = 0; j < A.M; j++){
                if(!(j == i)){
                    float scale = -A.get(j, i);
                    Guass::row_plus(j, scale, i, &A);
                    Guass::row_plus(j, scale, i, &B);
                }
            }
        }
    }
    return {A, B};
}

/**
 * @param A mxm for now
 * @param B mxn
 */
Matrix Solve::guass_back(Matrix A, Matrix B){
    float e = 1e-9f;

    for(int i = 0; i < A.M; i++){
        // pivot
        float max = 0.0f;
        int index = i;
        for(int j = i; j < A.M; j++){
            float value = abs(A.get(j, i));
            if(value > max){
                max = value;
                index = j;
            }
        }

        if(max > e){
            // swap 
            Guass::swap_row(i, index, &A);
            Guass::swap_row(i, index, &B);

            // scale
            float scale = 1.0f / A.get(i, i);
            Guass::scale_row(i, scale, &A);
            Guass::scale_row(i, scale, &B);

            // zero
            for(int j = i + 1; j < A.M; j++){
                float scale = -A.get(j, i);
                Guass::row_plus(j, scale, i, &A);
                Guass::row_plus(j, scale, i, &B);
            }
        }
    }

    return Solve::backward(A, B);
}














// takes in tridiagonall system and sovles it... 
// or do we just apply. lu and for /back sub? im not sure.... 

// Matrix Solve::thomas(Matrix A){
//     Matrix b = A.get_column(A.N - 1); 
//     A.resize(A.M, A.N - 1);


//     vector<float> E = {};
//     vector<float> F = {};
//     vector<float> R = {};


//     for(int k = 0; k < A.N; k++){

//         // L
//         float e; 
//         if(k - 1 < 0){
//             e = 0.0f;
//         } else {
//             e = A.get(k, k - 1) / F.at(k - 1); 
//         }

//         E.push_back(e);


//         // U
//         float f;
//         if(k - 1 < 0){
//             f = A.get(k, k);
//         } else {
//             f = A.get(k, k) - e * A.get(k - 1, k);
//         }
//         F.push_back(f);



//         // Forward Sub
//         float r; 
//         if(k - 1 < 0){
//             r = b.get(k, 0);
//         } else {
//             r = b.get(k, 0) - e * R.at(k - 1);
//         }
//         R.push_back(r);
//     }

//     // Backward Sub
//     vector<float> X(A.N);
//     for(int k = A.N - 1; k >= 0; k--){
//         float x; 
//         if(k + 1 >= A.N){
//             x =  R.at(k);
//             x /= F.at(k);
//         } else {
//             x =  R.at(k) - A.get(k, k + 1) * X.at(k + 1);
//             x /= F.at(k);
//         }

//         X[k] = x;
//     }

//     return Matrix(X.size(), 1, X);
// }







// // Edits by claude.....
// Matrix Solve::thomas(vector<float> a, vector<float> b, vector<float> c, vector<float> d){
//     int size = b.size(); 

//     vector<float> x(size);
//     vector<float> b_prime(size);
//     vector<float> d_prime(size);

//     // Initialize first elements
//     b_prime[0] = b[0];
//     d_prime[0] = d[0];

//     // Forward sweep
//     for(int i = 1; i < size; i++){
//         float w = a[i] / b_prime[i - 1]; 
//         b_prime[i] = b[i] - w * c[i - 1]; 
//         d_prime[i] = d[i] - w * d_prime[i - 1]; 
//     }

//     // Back substitution
//     x[size - 1] = d_prime[size - 1] / b_prime[size - 1];
//     for(int i = size - 2; i >= 0; i--){
//         x[i] = (d_prime[i] - c[i] * x[i + 1]) / b_prime[i];
//     }

//     return Matrix(size, 1, x);
// }























// input genreal formulas into thomas thing?.... for cubic spline thing or no?...

// Matrix Solve::thomas(vector<float> a, vector<float> b, vector<float> c, vector<float> d){
//     int size = a.size(); 

//     vector<float> x(size);

//     for(int i = 1; i < size; i++){
//         float w = a.at(i) / b.at(i - 1); 
//         b[i + 1] = b.at(i) - w * c.at(i - 1); 
//         d[i + 1] = d.at(i) - w * d.at(i - 1); 
//     }

//     x[size - 1] = (d.back() / b.back());
//     for(int i = size - 2; i >= 0; i--){
//         float value = d.at(i) - c.at(i) * x.at(i + 1);
//         value /= b.at(i);
//         x[i] = value;
//     }

//     return Matrix(size, 1, x);
// }







// Rewrite w/ A & B and X . where X and B can be matricies now & stuff...
// /**
//  * @param x Intial Guess
//  * @param w Relaxation Factor Omega (1.0f -> Guass Seidel)
//  */
// Matrix Solve::gauss_seidel(Matrix A, Matrix x, float w){

//     float thresh = 1e-3;
//     int size = x.data.size(); 
//     Matrix past_x = x;

//     bool exit = false;

//     for(int k = 0; k < 50; k++){
//         // New x
//         for(int i = 0; i < size; i++){
//             float sum = 0.0f;
//             for(int j = 0; j < size; j++){
//                 if(!(j == i)){
//                     sum += A.get(i, j) * x.data.at(j) * -1; 
//                 }
//             }
//             sum += A.get(i, A.N - 1);
//             sum /= A.get(i, i);

//             past_x = x;
//             x.data.at(i) = w * sum + (1.0f - w) * x.data.at(i); // Relaxation techinque 

//             if((x - past_x).L2() < thresh){
//                 cout << "converged\n";
//                 exit = true;
//                 break;
//             }
//         }       

//         if(exit){
//             break;
//         } else {
//             x.print(2);
//             cout << "\n";
//         }
//     }

//     return x;
// }





// column vector convention and stuff...


// for symetric & positive definite matrix?... 
// large and sparse?...

// Matrix Solve::conjugate_gradient(Matrix A, Matrix x){
//     float e = 1e-12;
//     Matrix b = A.get_column(A.N - 1);
//     A.resize(A.M, A.N - 1);


//     // Residual
//     Matrix pred = A * x; 
//     Matrix r = b - pred;
//     Matrix past_r(0, 0);

//     // P
//     Matrix p = r; 

//     // ............ 
//     for(int i = 0; i < 100; i++){
//         // Update x
//         float alpha = r.dot(r) / (p.T() * A * p).get(0, 0);
//         Matrix v = p.copy();
//         v.scale(alpha);
//         x = x + v; 

//         // Update residual 
//         pred = A * x; 
//         past_r = r;
//         r = b - pred;

//         if(r.L2() < e){
//             // solution found....
//             cout << "converged\n";
//             break;
//         } else {
//             // Update P
//             float beta = r.dot(r) / past_r.dot(past_r);
//             p.scale(beta); 
//             p = p + r;
//         }
//     }

//     return x;
    
// }

