#include "Interpolate.h"
#include "../Matrix/Solve.h"




Function Interpolate::lagrange(Matrix data, int n){
    vector<float> x = data.get_column(0).data;
    vector<float> y = data.get_column(1).data;

    Function P({}, 0.0f);
    for(int k = 0; k <= n; k++){
        Function f({1}, 0.0f); 
        float d = 1.0f;
        for(int i = 0; i <= n; i++){
            if(!(i == k)){
                f = f * Function({-x[i], 1}, 0.0f);
                d *= (x[k] - x[i]);
            }
        }

        float scale = y[k] / d;
        P = P + f * scale;
    }

    return P;
}



Peice Interpolate::peice_wise_lagrange(Matrix data, int n){
    vector<float> x = data.get_column(0).data;
    vector<float> y = data.get_column(1).data;

    int size = data.M / (n + 1);
    Peice peice;

    for(int z = 0; z < size; z++){
        int shift = z * (n + 1);
        Function P({}, 0.0f);
        for(int k = 0; k <= n; k++){
            Function f({1}, 0.0f); 
            float d = 1.0f;
            for(int i = 0; i <= n; i++){
                if(!(i == k)){
                    f = f * Function({-x[shift + i], 1}, 0.0f);
                    d *= (x[shift + k] - x[shift + i]);
                }
            }

            float scale = y[shift + k] / d;
            P = P + f * scale;
        }
        peice.append(P.values, 0.0f, x[shift], x[shift + n]);
    }

    return peice;
}












// // input nodes as x and y column vectors
// Peice Interpolate::natural_spline(Matrix nodes){
//     vector<float> x = nodes.get_column(0).data;
//     vector<float> y = nodes.get_column(1).data;

//     vector<float> H = {};
//     for(int i = 0; i < x.size() - 1; i++){
//         float h = x.at(i + 1) - x.at(i);
//         H.push_back(h);
//     }

//     vector<vector<float>> abcd = create_spline_system(x, y, H);
//     vector<float> C = Solve::thomas(abcd.at(0), abcd.at(1), abcd.at(2), abcd.at(3)).data;   

//     Peice peice; 
//     for(int j = 0; j < x.size() - 1; j++){  
//         float a = y[j];
//         float b = (y[j + 1] - y[j]) / H[j] - H[j] * (C[j + 1] + 2 * C[j]) / 3;  
//         float c = C[j];
//         float d = (C[j + 1] - C[j]) / (3 * H[j]);
        
//         peice.append(
//             {a, b, c, d},  // Coefficents
//             x[j],          // Center
//             x[j], x[j + 1] // Bounds
//         ); 
//     }
//     return peice;
// }

// vector<vector<float>> Interpolate::create_spline_system(vector<float> x, vector<float> y, vector<float> H) {
//     int n = x.size();

//     vector<float> a(n - 1, 0.0f); // lower diagonal
//     vector<float> b(n,     1.0f); // main diagonal
//     vector<float> c(n - 1, 0.0f); // upper diagonal
//     vector<float> d(n,     0.0f); // right-hand side

//     // Fill diagonals
//     for (int i = 1; i < n - 1; i++) {
//         a[i - 1] = H[i - 1];
//         b[i] = 2 * (H[i - 1] + H[i]);
//         c[i] = H[i];
//     }

//     // RHS
//     for (int i = 1; i < n - 1; i++) {
//         float value = (y[i] - y[i - 1]) / H[i - 1];
//         float next = (y[i + 1] - y[i]) / H[i];
//         d[i] = 3 * (next - value);
//     }

//     return {a, b, c, d};
// }