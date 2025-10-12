


#include "Function.h"
#include <iomanip>
// tags here as wel??... idk...
// x^0, x^1 ... x^n

Function::Function(vector<float> alpha){
    this->alpha = alpha; 
    this->center = 0.0f;
}

Function::Function(vector<float> alpha, float center){
    this->alpha = alpha; 
    this->center = center;
}

Function::Function(vector<float> alpha, vector<float> beta){
    this->alpha = alpha; 
    this->beta = beta;
    this->center = 0.0f;
}

Function::Function(vector<float> alpha, vector<float> beta, float center){
    this->alpha = alpha; 
    this->beta = beta;
    this->center = center;
}

float Function::at(float input){

    float sum = 0; // correct order?...
    for(int nth = 0; nth < alpha.size(); nth++){
        sum += alpha.at(nth) * pow(input - center, nth);
    }
    return sum;

    // return synth_rem(input);
}

float Function::deg(){ // or call DEG?...
    return (alpha.size() - beta.size());
}


Matrix Function::sample(float left, float right, float delta){
    int size = (right - left) / delta;
    Matrix output(size, 2, 0.0f);
    int index = 0;
    for(float i = left; i <= right; i += delta){
        output.set(index, 0, i);
        output.set(index, 1, at(i));
        index++;
    }
    return output;
}


Function Function::operator*(Function f){
    vector<float> data(alpha.size() + f.alpha.size() - 1, 0.0f);
    for(int i = 0; i < alpha.size(); i++){
        for(int j = 0; j < f.alpha.size(); j++){
            data[i + j] += alpha.at(i) * f.alpha.at(j);
        }
    }
    return Function(data, 0.0f);
}

/**
 * @returns {Q, R}
 */
vector<Function> Function::operator/(Function f){
    // if f is rational. multiply by recriprecal. 
    // then divide

    // syntheic division 
    if(f.alpha.size() == 2){

        float R;
        float C = f.alpha[1]; 
        f.alpha[0] = f.alpha[0] / f.alpha[1];
        f.alpha[1] = 1.0f;
        float value = alpha.back();
        vector<float> Q(alpha.size() - 1);
        Q[Q.size() - 1] = value;

        for(int i = alpha.size() - 2; i >= 0; i--){
            value *= -f.alpha[0];
            value += alpha[i];

            if(i == 0){
                R = value; // Remainder
            } else {
                Q[i - 1] = value;
            }
        }


        return {Function(Q) / C, Function({R}, f.alpha) / C};
    } else { // Long Division
        vector<float> Q(alpha.size() - f.alpha.size() + 1, 0.0f);
        Function R = *this; // dividend

        while(R.deg() >= f.deg()){
            float c = R.alpha.back() / f.alpha.back();
            Q[R.deg() - f.deg()] = c;
            R = R - f * c;
        }

        return {Function(Q), Function(R.alpha, f.alpha)};
    }

    // returns two functions...
}

Function Function::operator*(float scale){
    Function f = *this;
    for(int i = 0; i < f.alpha.size(); i++){
        f.alpha[i] *= scale;
    }
    return f;
}

Function Function::operator/(float scale){
    Function f = *this;
    for(int i = 0; i < f.alpha.size(); i++){
        f.alpha[i] /= scale;
    }

    // or multiply beta by scale?....
    return f;
}

Function& Function::operator*=(float scale) {
    for (int i = 0; i < alpha.size(); i++) {
        alpha[i] *= scale;
    }
    return *this;
}

Function& Function::operator/=(float scale) {
    for (int i = 0; i < alpha.size(); i++) {
        alpha[i] /= scale;
    }
    return *this;
}

Function Function::operator+(Function f){
    Function p = (Function(alpha) * Function(f.beta)) + (Function(beta) * Function(f.alpha));
    Function q = (*this) * f;
    return Function(p.alpha, q.alpha);
}

Function Function::operator-(Function f){
    vector<float> data(max(alpha.size(), f.alpha.size()), 0.0f);
    for(int i = 0; i < alpha.size(); i++){
        data[i] += alpha[i];
    }

    for(int i = 0; i < f.alpha.size(); i++){
        data[i] -= f.alpha[i];
    }

    return Function(data);
}
Function& Function::operator-=(Function f) {
    *this = *this - f;  // Reuse operator-
    return *this;
}

float Function::integrate(float a, float b){
    Function f = *this;
    f.alpha.push_back(0.0f);
    for(int i = f.alpha.size() - 1; i > 0; i--){
        f.alpha[i] = f.alpha[i - 1] / i;
    }
    return f.at(b) - f.at(a);
}

Function Function::derivative(){
    vector<float> alpha = {};

    for(int nth = 1; nth < this->alpha.size(); nth++){
        alpha.push_back(this->alpha.at(this->alpha.size() - nth - 1) * nth);
    }

    return Function(alpha);
}






// gpt generated
void printPoly(vector<float>& coeffs, float center, int decimals) {
    cout << fixed << setprecision(decimals);

    bool firstTerm = true;
    for (int i = 0; i < coeffs.size(); ++i) {
        float coeff = coeffs[i];

        // Skip zero coefficients
        if (abs(coeff) < 1e-9) continue;

        // Handle sign
        if (!firstTerm) {
            if (coeff >= 0)
                cout << " + ";
            else
                cout << " - ";
        } else {
            if (coeff < 0)
                cout << "-";
            firstTerm = false;
        }

        // Print coefficient magnitude (omit 1 if not constant)
        float absCoeff = abs(coeff);
        if (!(absCoeff == 1.0f && i > 0))
            cout << absCoeff;

        // Print variable part
        if (i >= 1) {
            if (center == 0) {
                cout << "x";
            } else {
                cout << "(x";
                if (center > 0)
                    cout << " - " << center;
                else
                    cout << " + " << -center;
                cout << ")";
            }

            if (i >= 2)
                cout << "^" << i;
        }
    }

    if (firstTerm)
        cout << "0";
}

void Function::print(int n) {
    std::cout << "alpha: ";
    printPoly(alpha, center, n);
    std::cout << "\n";

    std::cout << "beta:  ";
    printPoly(beta, center, n);
    std::cout << "\n\n";
}






























// general integral return?....








// float Function::nth_at(float nth, float value){


//     Function f = *this;
    
//     // Perform synthetic division nth times
//     for(int i = 0; i < nth; i++) {
//         f = f.synth_quot(value);  // Get quotient for next iteration
//     }
    
//     // Get the remainder (coefficient of the reduced polynomial)
//     float remainder = f.synth_rem(value);
    
//     // Multiply by n! to get the actual nth derivative
//     int factorial = 1;
//     for(int i = 2; i <= nth; i++) {
//         factorial *= i;
//     }
    
//     return remainder * factorial;
// }   

















// calude synth div version...

// float C = f.alpha[1];
//         float R = alpha[0];
//         vector<float> Q(alpha.size() - 1);

//         for(int i = alpha.size() - 1; i > 0; i--){
//             Q[i - 1] = alpha[i];
//             R -= Q[i - 1] * f.alpha[0];
//         }

//         return {Function(Q) / C, Function({R}, f.alpha) / C};