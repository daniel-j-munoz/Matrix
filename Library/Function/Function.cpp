


#include "Function.h"
#include <iomanip>

#include "Variable.h"



Function::Function(Sparse alpha){
    this->alpha = alpha;
    this->center = 0.0f;
}

Function::Function(Sparse alpha, Sparse beta){
    this->alpha = alpha;
    this->beta = beta;
    this->center = 0.0f;
}


// float Function::at(Sparse tensor, vector<float> x){
//    // index for all dimensions
// }


// float Function::at(vector<float> x){
//     return at(alpha, x) / at(beta, x);
// }


Sparse FOIL(Sparse A, Sparse B){

    vector<Entry> entries = {};
    Sparse output(entries);

    for(Entry a : A.entries){
        for(Entry b : B.entries){

            vector<int> dim = a.dim;
            vector<int> index = a.index;


            for(int i = 0; i < b.dim.size(); i++){
                // Search
                bool found = false;
                for(int j = 0; j < dim.size(); j++){
                    if(b.dim[i] == dim[j]){
                        index[j] += b.index[i];
                        found = true;
                    }
                }

                if(!found){
                    dim.push_back(b.dim[i]);
                    index.push_back(b.index[i]);
                }
            }

            output.add(Entry(dim, index, a.value * b.value));
        }
    }
    return output;
}

Function Function::operator*(Function other){
    alpha = FOIL(alpha, other.alpha);
    beta = FOIL(beta, other.beta);
    return Function(alpha, beta);
}

Function Function::plus(Function function){
    Function output(alpha + function.alpha);
    return output;
}

Function Function::operator+(Function f){
    Function p = (Function(alpha) * Function(f.beta)).plus(Function(beta) * Function(f.alpha));
    Function q = Function(beta) * Function(f.beta); // lcm instead?...
    return Function(p.alpha, q.alpha);
}

Function Function::operator-(Function f){
    return (*this) + (f * -1.0f);
}

Function Function::operator*(float scale){
    return alpha * scale;
}

Function Function::operator/(float scale){
    return operator*(1.0f / scale);
}


Function Function::operator^(int power){
    if(power == 1){
        return *this;
    } else if(power == 0){ // indeterminate forms?...
        return Function(Sparse({Entry({0}, {0}, 1.0f)}));
    } else if(power < 0){
        power = abs(power);
        flip();
    } 

    Function output = *this;
    for(int i = 0; i < power - 1; i++){
        output = output * (*this);
    }
    return output;
}






vector<Function> Function::group(int dim){

    vector<int> index = {};
    vector<Function> output = {};

    for(Entry entry : alpha.entries){


        // find correct dim
        for(int i = 0; i < entry.dim.size(); i++){
            if(entry.dim[i] == dim){

                // search for same index
                for(int j = 0; j < index.size(); i++){
                    if(entry.index[i] == index[j]){
                        // remove group variable thing..
                        output[j].alpha.add(entry); // add the entry but exlcuding the dim group variable
                    }
                }

                // not found then append new index & gorup new output
                // if(!found){}
                // index.push_back(this->index[i])
                // 
            }
        }




    }

}






void Function::flip(){
    Sparse past_alpha = alpha;
    alpha = beta;
    beta = past_alpha;
}








// handle order as wel??...
void print_mvp(Sparse alpha, float center, int n){
    bool first = true;
    for(Entry entry : alpha.entries){
        string output = "";

        // plus or minus
        if(entry.value > 0 && !first){
            output += " + ";
        } else if(entry.value < 0){
            if(first){
                output += "-";
            } else {
                output += " - ";
            }
        }
        first = false;

        cout << output;
        output = "";

        // variables
        bool has_variables = false;
        for(int j = 0; j < entry.dim.size(); j++){
            int index = entry.index[j];
            if(!(index == 0)){
                has_variables = true;
                output += Variable::map.pre_image(entry.dim[j]);
                if(!(index == 1)){
                    output += "^(";
                    output += to_string(index);
                    output += ")";
                }
            }
        }     

        // Coefficent
        if(!(entry.value == 1.0f) || !has_variables){
            cout << fixed << setprecision(n) << abs(entry.value);
        }

        cout << output;
    }

    cout << "\n";
}

void Function::print(int n) {
    std::cout << "alpha: ";
    print_mvp(alpha, center, n);
    std::cout << "\n";

    std::cout << "beta:  ";
    print_mvp(beta, center, n);
    std::cout << "\n\n";
}







// float Function::deg(int dim){
//     return (alpha.shape[dim] - beta.shape[dim]);
// }


//var map? ... map?... idk... other names?.... idk...
// long division
// partial derivative & integerate w/ respect to some variable?...
// function evulation w/ synth div or sum?
// ruffini rule?...
// general integral return?....
// nth derivative w/ synth div?...



// so now i guess we sort of handle the data 
// of x and y sepearlty now. 
// rather than keeping them together... 
// just writing what comes to head....

// /**
//  * a & b are bounds for each variable inclusive
//  */
// vector<Matrix> Function::sample(vector<float> a, vector<float> b, vector<float> delta){
//     // each row is a sample. 
//     // each col is element of index 
//     // or element of ouput basically
//     Matrix x(0, 0); // domain
//     Matrix y(0, 0); // codomain
    
//     vector<float> index = a; 
//     bool done = false;
//     while (!done) {
//         x.add_row(index);
//         y.add_row({at(index)});

//         for (int dim = index.size() - 1; dim >= 0; dim--) {
//             index[dim] += delta[dim];
//             if (index[dim] < b[dim]) {
//                 break;
//             }
//             index[dim] = a[dim];

//             if (dim == 0) {
//                 done = true;
//             }
//         }
//     }

//     return {x, y};
// }

// Define boundary for sampling beyond just a rectangular region?...
// some sort of partial at. dim and index?... retruns function. so kind of like a level curve soemting like that...
