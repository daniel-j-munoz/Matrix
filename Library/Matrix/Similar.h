// // similar transformations?...
// // is this a good place to put upper hessenberg?....


//      // Obtain a similar triadognal matrix
//         // Retains Eigenvalues
//         Matrix upper_hessenberg();


// // i recall there only being n - 2 transformation from somewhere...

// // Does this require the matrix to be squared?....

// // i believe the matrix must be n x n. but im not sure...
// /**
//  * Returns as upper Hessenberg matrix
//  * If symmetric, returns as tridiagonal matrix 
//  * in both cases, the returned matrix retains eigenvalues/eigenvectors 
//  * aka the matrix is similar.
//  * 
//  * there might be some exceptions that i am possibly unaware of.
//  * i am not sure...
//  * 
//  * can be used as a good intial starting point for QR algorithms
//  */
// Matrix Matrix::upper_hessenberg(){
//     Matrix A = *this;

//     for(int k = 0; k < N - 2; k++){ 
//         Matrix x = A.get_column(k); 

//         // Zeros
//         for(int i = 0; i <= k; i++){
//             x.set(i, 0, 0.0f);
//         }

//         // Standard Basis & Get Vector 
//         float sign = (x.get(k + 1, 0) >= 0) ? 1.0f : -1.0f; /// NEW STEP HERE
//         Matrix b(M, 1, 0.0f);
//         b.set(k + 1, 0, sign * x.magnitude());
//         x = x - b;

//         if(x.magnitude() > 1e-6){
//             x.unit_mag();

//             // H
//             Matrix I(M, M); 
//             Matrix xt = x.T();
//             Matrix xxt = x * xt;
//             xxt.scale(2.0f);
//             Matrix H = I - xxt;

//             // HAHT 
//             Matrix HT = H.T();
//             A = H * A * HT; 
//         } else {
//             break;
//         }
        
//     }

//     return A;
// }