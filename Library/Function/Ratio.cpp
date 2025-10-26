// #include "Ratio.h"

// // coprime tags?...

// Ratio::Ratio(Function alpha, Function beta) : alpha(alpha), beta(beta){
//     cancel();
// }

// Ratio Ratio::operator+(Ratio r){
//     Function LCM = beta.lcm(r.beta);
//     Ratio copy = *this;
//     copy.alpha = alpha * (LCM / beta)[0] + r.alpha * (LCM / r.beta)[0]; 
//     copy.beta = LCM;
//     return copy;
// }

// Ratio Ratio::operator+(Function f){
//     // return *this + Ratio(f, Function())
// }

// Ratio Ratio::operator*(Ratio r){
//     Ratio copy = *this;
//     copy.alpha *= r.alpha;
//     copy.beta *= r.beta;
// }


// Ratio Ratio::operator/(Ratio r){
//     r.flip();
//     return *this * r;
// }

// void Ratio::flip(){
//     Function past_alpha = alpha;
//     alpha = beta;
//     beta = past_alpha;
// }

// void Ratio::cancel(){
//     Function GCF = alpha.gcf(beta);
//     alpha /= GCF;
//     beta /= GCF;
// }

// vector<Function> Ratio::divide(){
//     return alpha / beta;
// }