#include "Area.h"
#include "Interpolate.h"
#include "../Matrix/Data.h"
#include "Root.h"


// float Area::newton_cote(Matrix data, int n){
//     Matrix x = data.get_column(0);
//     Peice peice = Interpolate::peice_wise_lagrange(data, n);
//     return peice.integrate(Data::min(x)[0], Data::max(x)[0]);
// }




// float Area::guass_legendre(Matrix data){

//     Matrix x = data.get_column(0);
//     vector<float> y = data.get_column(1).data;

//     Data::range(-1, 1, &data);

//     Function P = legendre(data.M);
//     Function dP = P.derivative();
//     vector<float> roots = Root::newton_horner(vector<float>(data.M, 0.0f), P).data;
//     vector<float> omega = {};

//     for(float root : roots){
//         float value = 2.0f / (
//             (1.0f - root * root) * pow(dP.at(root), 2.0f)
//         );
//         omega.push_back(value);
//     }

//     float area = 0.0f;
//     for(int i = 0; i < roots.size(); i++){
//         int index = Data::nn(roots[i], x);
//         area += y[index] * omega[i];
//     }

//     return area;
// }




// Function Area::legendre(int n){
//     vector<Function> P = {Function({1}, 0.0f), Function({0, 1}, 0.0f)};

//     for(int i = 2; i <= n; i++){
//         P[i] = P[1] * P[i - 1] * (2 * n + 1) - P[i - 2] * n;
//         P[i] /= (n + 1);
//     }

//     // another method that returns the list as well?...
//     return P.back();
// }


