#include "Solve.h"

// this is guass seidel right?... not jacobi right?....
// better stopping criteria?...

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