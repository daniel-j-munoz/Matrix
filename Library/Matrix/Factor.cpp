
#include "Factor.h"
#include "Data.h"
#include "Guass.h"

// Accepts Non Square Matricies as Well 
// QR via Gram Schimdt Process
vector<Matrix> Factor::QR(Matrix A){
    vector<Matrix> U = {};

    // Gram Schimdt Process
    for(int k = 0; k < A.N; k++){
        Matrix a = A.get_column(k);
        Matrix sum(A.M, 1, 0.0f);
        for(int j = 0; j < k; j++){
            Matrix projection = a.project(U.at(j));
            sum += projection;
        }
        U.push_back(a - sum);
    }

    Matrix Q(A.M, 0);  
    for(Matrix column : U){
        Data::unit_L2(&column);
        Q.add_column(column.data);
    }

    Matrix R(A.M, A.N, 0);
    for(int i = 0; i < A.N; i++){
        Matrix a = A.get_column(i);
        for(int j = 0; j <= i; j++){
            Matrix e = Q.get_column(j);
            R.set(j, i, a.dot(e));
        }
    }

    return {Q, R};
}

/**
 * QR via House Holder
 */

 // measure perforamnce differnce for differnt methods and way fo doing things?...

 //  maybe don't copmute all house holders?... dpends on the speicifc case?.....
 // might be useful for better computation?... who knows...

 // i think this might work for any type of matrix?.... not just square matrix?...
// can QRHH be better written more efficent?...
// QR aitken method?.... 
// accerlating convergece in someway?....

vector<Matrix> Factor::QRHH(Matrix A){
    Matrix Q(A.M, A.M); // Identity Matrix
    Matrix R = A.copy(); // A
    vector<Matrix> HH = {}; // Householders

    for(int k = 0; k < A.N; k++){
        // Get Column Vector
        Matrix x = R.get_column(k);

        // Zero 
        for(int i = 0; i < k; i++){
            x.set(i, 0, 0.0f);
        }

        // Basis Vector
        Matrix vec(A.M, 1, 0.0f); 
        vec.set(k, 0, 1.0f);

        // V
        float sign = (x.get(k, 0) >= 0) ? 1.0f : -1.0f; /// NEW STEP HERE
        vec.scale(sign * x.L2()); // ADDED SIGN *
        x = x - vec; 

        if(x.L2() > 1e-6){ // Avoid Division By Zero
            Data::unit_L2(&x);

            // Householder Matrix
            Matrix I(A.M, A.M);
            // H = I - 2(x*xt)
            Matrix xt = x.T();
            vec = x * xt;
            vec.scale(2);
            Matrix H = I - vec;
            HH.push_back(H);

            // QR
            Q = Q * H;
            R = H * R;

            cout << k << "\n";
        } else {
            break;
        }
    }

    return {Q, R};
}





/**
 * Hermitatian & Positive Definite
 */
vector<Matrix> Factor::cholesky(Matrix A){
    Matrix L(A.M, A.N, 0.0f);

    for(int i = 0; i < A.N; i++){
        for(int j = 0; j <= i; j++){
            // Diagonal elements
            if(i == j){
                float value = A.get(i, i); 
                for(int k = 0; k < j; k++){
                    value -= L.get(i, k) * L.get(i, k);
                }
                value = sqrt(value);
                L.set(i, j, value);
            } 
            // Off-diagonal elements
            else {
                float value = A.get(i, j); 
                for(int k = 0; k < j; k++){
                    value -= L.get(i, k) * L.get(j, k);
                }
                value /= L.get(j, j);
                L.set(i, j, value);
            }
        }
    }   

    return {L, L.T()};
}


/**
 * @returns {P, L, U}
 */
vector<Matrix> Factor::LU(Matrix A){
    Matrix L(A.M, A.M); 
    Matrix P(A.M, A.M); // Idneity Matricies

    int index = 0; // pivot row
    for(int i = 0; i < A.N; i++){
        // Partial Pivoting
        float max = 0.0f; 
        int new_j = index; 
        for(int j = index; j < A.M; j++){
            if(abs(A.get(j, i)) > max){
                max = abs(A.get(j, i));
                new_j = j;
            }
        }
        
        if(!(max == 0.0f)){
            // Pivot Matrix
            Guass::swap_col(index, new_j, &P);
            Guass::swap_row(index, new_j, &L);
            Guass::swap_col(index, new_j, &L);
            Guass::swap_row(index, new_j, &A);

            // U
            for(int j = index + 1; j < A.M; j++){
                float s = A.get(j, i) / A.get(index, i);  
                L.set(j, i, s); 
                Guass::row_plus(j, -s, index, &A); // rowj -= s * rowi
            }

        }
        
        index++; 
        if(index >= A.M){
            break;
        }
    }

    return {P, L, A};
}
