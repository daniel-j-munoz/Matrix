
#include "Root.h"
#include <iomanip>

float sign(float x){
    if(x > 0){
        return 1.0f;
    } else {
        return -1.0f;
    }
}

// float Root::newton(float xo, Function function){
//     Function d_function = function.derivative();
//     float x = xo;
//     float e = 1e-6;

//     for(int i = 0; i < 1000; i++){
//         if(abs(d_function.at({x})) < e || abs(x - xo) > 1e+6){ // Avoid Division by Zero
//             throw::runtime_error("diverged"); // diverged?...
//         } else {
//             float dx = function.at({x}) / d_function.at({x});
//             x -= dx;
//             if(abs(dx) < e){
//                 cout << "converged\n";
//                 break;
//             }
//         }
//     }

//     return x;
// }

// Matrix Root::newton_horner(vector<float> xo, Function f){ // return matrix or vector of flaot?...
//     vector<float> roots = {};
//     for(int i = 0; i < f.alpha.data.size() - 1; i++){
//         float root = newton(xo.at(i), f);
//         roots.push_back(root);
//         f = (f / Function({-root, 1}))[0]; // Deflation
//     }
//     return Matrix(roots.size(), 1, roots);
// }


// /**
//  * f(a)f(b) < 0
//  */

//  // differnt weight for a and b?

// void Root::bisection(float a, float b){

//     for(int i = 0; i < 50; i++){
//         float c = (a + b) / 2.0f;
//         cout << c << "\n";

//         if(function.at(a) * function.at(c) < 0){
//             b = c; 
//         } else {
//             a = c;
//         }

//     }
    
// }

// // similar to bisection. but instead of midpoint.
// //  we basically find intersection of axis and secant line formed by a,b and f(a),f(b)
// void Root::false_position(float a, float b){
//     for(int i = 0; i < 50; i++){
//         float m = (function.at(b) - function.at(a)) / (b - a);
//         float c = b - function.at(b) / m;
//         cout << c << "\n";

//         if(function.at(a) * function.at(c) < 0){
//             b = c; 
//         } else {
//             a = c;
//         }

//     }
// }

// // from line to paraobal. what about nth degree? so sort of like taylor? interseting...

// // not sure if working...
// void Root::muller(float x0, float x1, float x2){
//     for(int i = 0; i < 20; i++){
//         float h0 = x1 - x0;
//         float h1 = x2 - x1;
//         float d0 = (function.at(x1) - function.at(x0)) / h0; 
//         float d1 = (function.at(x2) - function.at(x1)) / h1;
//         float a = (d1 - d0) / (h0 + h1);
//         float b = a * h1 + d1;
//         float c = function.at(x2);

//         float x3 = x2 - (2 * c) / (b - sign(a)*sqrt(b * b - 4 * a * c));
//         cout << x3 << "\n";

//         x0 = x1; 
//         x1 = x2;
//         x2 = x3;

//     }
    
// }


