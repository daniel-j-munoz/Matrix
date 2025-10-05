#include "Solve.h"

// this is guass seidel right?... not jacobi right?....
// better stopping criteria?...

#include "Factor.h"

/**
 * @param x Intial Guess
 * @param w Relaxation Factor Omega (1.0f -> Guass Seidel)
 */
Matrix Solve::gauss_seidel(Matrix A, Matrix x, float w){

    float thresh = 1e-3;
    int size = x.data.size(); 
    Matrix past_x = x;

    bool exit = false;

    for(int k = 0; k < 50; k++){
        // New x
        for(int i = 0; i < size; i++){
            float sum = 0.0f;
            for(int j = 0; j < size; j++){
                if(!(j == i)){
                    sum += A.get(i, j) * x.data.at(j) * -1; 
                }
            }
            sum += A.get(i, A.N - 1);
            sum /= A.get(i, i);

            past_x = x;
            x.data.at(i) = w * sum + (1.0f - w) * x.data.at(i); // Relaxation techinque 

            if((x - past_x).magnitude() < thresh){
                cout << "converged\n";
                exit = true;
                break;
            }
        }       

        if(exit){
            break;
        } else {
            x.print(2);
            cout << "\n";
        }
    }

    return x;
}







// column vector convention and stuff...


// for symetric & positive definite matrix?... 
// large and sparse?...

Matrix Solve::conjugate_gradient(Matrix A, Matrix x){
    float e = 1e-12;
    Matrix b = A.get_column(A.N - 1);
    A.resize(A.M, A.N - 1);


    // Residual
    Matrix pred = A * x; 
    Matrix r = b - pred;
    Matrix past_r(0, 0);

    // P
    Matrix p = r; 

    // ............ 
    for(int i = 0; i < 100; i++){
        // Update x
        float alpha = r.dot(r) / (p.T() * A * p).get(0, 0);
        Matrix v = p.copy();
        v.scale(alpha);
        x = x + v; 

        // Update residual 
        pred = A * x; 
        past_r = r;
        r = b - pred;

        if(r.magnitude() < e){
            // solution found....
            cout << "converged\n";
            break;
        } else {
            // Update P
            float beta = r.dot(r) / past_r.dot(past_r);
            p.scale(beta); 
            p = p + r;
        }
    }

    return x;
    
}

























// Direct Methods.........

// another rref where we find uppper or lower triangular then back or foward subistion? 
// guass elm w/ back or forward subsition?...

// RREF Isnt working for some reason. find why out why this is the case...
Matrix Solve::rref(Matrix A){

    Matrix X = A.copy();

    // for each column 
    for(int n = 0; n < X.N; n++){

        // Non Zero Element
        int non_zero = n; 
        for(int m = 0; m < X.M; m++){
            if(!(X.get(m, n) == 0.0f)){
                non_zero = m; 
                break; 
            }
        } 

        // Swap & Scale
        X.swap_row(n, non_zero); 
        X.scale_row(non_zero, 1.0f / X.get(non_zero, n));

        // Remove other Non Zero Elements
        for(int m = 0; m < X.M; m++){
            if(!(m == non_zero)){
                float element = X.get(m, n); 
                for(int ith = 0; ith < X.N; ith++){
                    X.set(
                        m, ith, 
                        X.get(m, ith) - element * X.get(non_zero, ith)
                    );
                }
            }
        }
    }

    return X;
}














// Uses the idea of back and foward subsittuion w/ triangular matricies. 

Matrix Solve::LU(Matrix A){
    Matrix b = A.get_column(A.N - 1);
    A.resize(A.M, A.N - 1);

    vector<Matrix> LU = Factor::LU(A);
    
    // Ly = b Foward Substitution
    Matrix one = LU.at(0);
    one.add_column(b);
    Matrix y = foward(one);

    // Ux = y Back Substitution 
    Matrix two = LU.at(1);
    two.add_column(y);
    return backward(two);
}

// requires that the matrix be symmetric(thus square as well?) and positive definite?....
Matrix Solve::cholesky(Matrix A){
    Matrix b = A.get_column(A.N - 1);
    A.resize(A.M, A.N - 1);

    vector<Matrix> LLT = Factor::cholesky(A);

    // Foward Sub Ly = b 
    Matrix one = LLT.at(0);
    one.add_column(b);
    Matrix y = foward(one);

    // Backward Sub LTx = y
    Matrix two = LLT.at(1); 
    two.add_column(y); 
    return backward(two);
}


// maybe A and b form  might be usefull ?... 
// instead of just augemented matrix.... im not sure tbh though....
// OR PERHAPS EVEN... just accept both forms......?..... if agumented, just seperate and send to other method w/ A and b parameters?.....

/**
 * input lower triangular matrix
 * 
 * does it have to be lower triangular for foward sub?.... im pretty surre right?....
 */
Matrix Solve::foward(Matrix A){
    Matrix b = A.get_column(A.N - 1);
    A.resize(A.M, A.N - 1);

    vector<float> x = {};
    for(int j = 0; j < A.M; j++){
        float xj = b.get(j, 0);
        for(int i = 0; i < j; i++){
            xj -= A.get(j, i) * x.at(i);
        }
        xj /= A.get(j, j);  // ← MISSING THIS LINE! According to claude.... i think i forget this line?... idk double check and stuff......
        x.push_back(xj);
    }

    return Matrix(x.size(), 1, x);
}


// Ux = y
Matrix Solve::backward(Matrix A){
    Matrix b = A.get_column(A.N - 1);
    A.resize(A.M, A.N - 1);

    vector<float> x(A.M);
    for(int j = A.M - 1; j >= 0; j--){
        float xj = b.get(j, 0); 
        for(int i = j + 1; i < A.M; i++){
            xj -= A.get(j, i) * x.at(i);
        }
        xj /= A.get(j, j);
        x[j] = xj;
    }
    return Matrix(x.size(), 1, x);
}










// subdiagonal and main diagonal arrays?....
// interseting...



// takes in tridiagonall system and sovles it... 
// or do we just apply. lu and for /back sub? im not sure.... 

Matrix Solve::thomas(Matrix A){
    Matrix b = A.get_column(A.N - 1); 
    A.resize(A.M, A.N - 1);


    vector<float> E = {};
    vector<float> F = {};
    vector<float> R = {};


    for(int k = 0; k < A.N; k++){

        // L
        float e; 
        if(k - 1 < 0){
            e = 0.0f;
        } else {
            e = A.get(k, k - 1) / F.at(k - 1); 
        }

        E.push_back(e);


        // U
        float f;
        if(k - 1 < 0){
            f = A.get(k, k);
        } else {
            f = A.get(k, k) - e * A.get(k - 1, k);
        }
        F.push_back(f);



        // Forward Sub
        float r; 
        if(k - 1 < 0){
            r = b.get(k, 0);
        } else {
            r = b.get(k, 0) - e * R.at(k - 1);
        }
        R.push_back(r);
    }

    // Backward Sub
    vector<float> X(A.N);
    for(int k = A.N - 1; k >= 0; k--){
        float x; 
        if(k + 1 >= A.N){
            x =  R.at(k);
            x /= F.at(k);
        } else {
            x =  R.at(k) - A.get(k, k + 1) * X.at(k + 1);
            x /= F.at(k);
        }

        X[k] = x;
    }

    return Matrix(X.size(), 1, X);
}






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

// Edits by claude.....
Matrix Solve::thomas(vector<float> a, vector<float> b, vector<float> c, vector<float> d){
    int size = b.size(); 

    vector<float> x(size);
    vector<float> b_prime(size);
    vector<float> d_prime(size);

    // Initialize first elements
    b_prime[0] = b[0];
    d_prime[0] = d[0];

    // Forward sweep
    for(int i = 1; i < size; i++){
        float w = a[i] / b_prime[i - 1]; 
        b_prime[i] = b[i] - w * c[i - 1]; 
        d_prime[i] = d[i] - w * d_prime[i - 1]; 
    }

    // Back substitution
    x[size - 1] = d_prime[size - 1] / b_prime[size - 1];
    for(int i = size - 2; i >= 0; i--){
        x[i] = (d_prime[i] - c[i] * x[i + 1]) / b_prime[i];
    }

    return Matrix(size, 1, x);
}








// iterative refifement just improves the guesses each iteration?...






// so imagine the matrix having tags. and being able to choice better omegas, given what type of matrix we have and stuff...
// just writing what comes to head...

// and so what if omega could perhaps be viewed as something like a learnable parameter. 
// what if we get multiple matricies. Input their elements into a MLP Model and predict an omega. 
// That way, we could make a prediction of an omega given our current matrix...

// is mlp model a hgiher dimensional form of regression or something?..... or maybe not?....
// higher dimensional regression?... in general?... given input and output. 
// Make prediction of general function that could approximate the thing?... interesting...





// guasssiedel might be used for large matricies instead of rref for computation?...who knows.... 
// what might be the benefit of numerical vs direct meethod here... idk but pretty iknteresting... just writing what comes to head...