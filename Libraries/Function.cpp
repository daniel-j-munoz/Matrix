


#include "Function.h"
#include <iomanip>


// x^0, x^1 ... x^n
Function::Function(vector<float> values, float center){
    this->values = values; 
    this->center = center;
}

float Function::at(float input){

    float sum = 0; // correct order?...
    for(int nth = 0; nth < values.size(); nth++){
        sum += values.at(nth) * pow(input - center, nth);
    }
    return sum;

    // return synth_rem(input);
}

// float Function::synth_rem(float value){
//     float top;
//     float bot = 0.0f;
//     float rem;

//     for(int ith = 0; ith < values.size(); ith++){
//         float sum;
//         top = values.at(ith); 
//         sum = top + bot;
//         rem = sum;

//         bot = sum * value; 
//     }

//     return rem;
// }

// Function Function::synth_quot(float value){

//     vector<float> new_values = {};
//     float top;
//     float bot = 0.0f;

//     for(int ith = 0; ith < values.size() - 1; ith++){
//         float sum;
//         top = values.at(ith); 
//         sum = top + bot;
//         new_values.push_back(sum);
//         bot = sum * value; 
//     }

//     return Function(new_values);
// }


// Function Function::derivative(){
//     vector<float> values = {};

//     for(int nth = 1; nth < this->values.size(); nth++){
//         values.push_back(this->values.at(this->values.size() - nth - 1) * nth);
//     }

//     return Function(values);
// }


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



















// /**
//  * Inclusive bounds
//  * Returns {domain, codomain}
//  */
// vector<vector<float>> Function::sample(float a, float b, float delta){

//     vector<float> domain = {};
//     vector<float> codomain = {};

//     for(float x = a; x <= b; x += delta){
//         domain.push_back(x); 
//         codomain.push_back(at(x));
//     }

//     return {domain, codomain};
// }

// void Function::output_sample(float a, float b, float delta){
//     vector<vector<float>> sample = this->sample(a, b, delta);
//     cout << "n      x_n       f(x_n)\n";
//     for(int i = 0; i < sample.at(0).size(); i++){
//         cout << i << setw(10) << sample.at(0).at(i) << "" << setw(12) << sample.at(1).at(i) << "\n";
//     }
// }