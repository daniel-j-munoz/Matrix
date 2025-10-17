


#include "Function.h"
#include <iomanip>
// tags here as wel??... idk...
// x^0, x^1 ... x^n


// negative degrees?.... how to handle....

Tensor Function::to_tensor(vector<float> data){
    return Tensor(data);
}

Function::Function(vector<float> alpha){
    this->alpha = to_tensor(alpha);
    this->beta = Tensor({1}, 1.0f);
    this->center = 0.0f;
}

Function::Function(vector<float> alpha, float center){
    this->alpha = to_tensor(alpha);
    this->beta = Tensor({1}, 1.0f);
    this->center = center;
}

Function::Function(vector<float> alpha, vector<float> beta){
    this->alpha = to_tensor(alpha);
    this->beta = to_tensor(beta);
    this->center = 0.0f;
}

Function::Function(vector<float> alpha, vector<float> beta, float center){
    this->alpha = to_tensor(alpha);
    this->beta = to_tensor(beta);
    this->center = center;
}

Function::Function(Tensor alpha){
    this->alpha = alpha;
    this->beta = Tensor({1}, 1.0f);
    this->center = 0.0f;
}

Function::Function(Tensor alpha, float center){
    this->alpha = alpha;
    this->beta = Tensor({1}, 1.0f);
    this->center = center;
}

Function::Function(Tensor alpha, Tensor beta){
    this->alpha = alpha;
    this->beta = beta;
    this->center = 0.0f;
}

Function::Function(Tensor alpha, Tensor beta, float center){
    this->alpha = alpha;
    this->beta = beta;
    this->center = center;
}

vector<float> get_swap(Map<string, int> newmap, Map<string, int> map){
    vector<float> swap(newmap.size()); 
    for(int dim = 0; dim < newmap.size(); dim++){
        int new_dim = newmap.image(map.domain[dim]);
        swap[new_dim] = dim; 
    }
    return swap;
}
// inverse. swap alpha and beta?...

// well its kind of like union minus intersection because thre common elements right?....




void Function::rerank(int rank){
    alpha = alpha.rerank(rank);
    beta = beta.rerank(rank);
}

void Function::transpose(vector<float> swap){
    alpha = alpha.T(swap);
    beta = beta.T(swap);
}






void remap_me(Function* a, Function* b){
    Map<string, int> map = Map<string, int>::merge(a->map, b->map);
    map.print();


    
    a->rerank(map.size() - a->map.size());
    b->rerank(map.size() - b->map.size());

    a->beta.print_shape();
    b->beta.print_shape();

    a->map.merge(map);
    b->map.merge(map);


    // a->transpose(get_swap(map, a->map));
    // b->transpose(get_swap(map, b->map));

    // // seperate make union & remap?.... idk....

    // Tensor::make_union({&a->alpha, &a->beta, &b->alpha, &b->beta});
}


Function Function::plus(Function function){
    remap_me(this, &function);
    Function output(alpha + function.alpha); // needs same var map as well...
    output.map = map;
    return output;
}





float Function::at(Tensor tensor, vector<float> x){
    float sum = 0.0f;
    for(int i = 0; i < tensor.data.size(); i++){
        Matrix point = tensor.point(i);
        float pro = tensor.data[i];
        for(int j = 0; j < point.M; j++){
            pro *= pow(x[j], point.get(j, 0));
        }   
        sum += pro;
    }
    return sum;
}

float Function::at(vector<float> x){
    return at(alpha, x) / at(beta, x);
}



// so now i guess we sort of handle the data 
// of x and y sepearlty now. 
// rather than keeping them together... 
// just writing what comes to head....

/**
 * a & b are bounds for each variable inclusive
 */
vector<Matrix> Function::sample(vector<float> a, vector<float> b, vector<float> delta){
    // each row is a sample. 
    // each col is element of index 
    // or element of ouput basically
    Matrix x(0, 0); // domain
    Matrix y(0, 0); // codomain
    
    vector<float> index = a; 
    bool done = false;
    while (!done) {
        x.add_row(index);
        y.add_row({at(index)});

        for (int dim = index.size() - 1; dim >= 0; dim--) {
            index[dim] += delta[dim];
            if (index[dim] < b[dim]) {
                break;
            }
            index[dim] = a[dim];

            if (dim == 0) {
                done = true;
            }
        }
    }

    return {x, y};
}

// Define boundary for sampling beyond just a rectangular region?...


Tensor Function::FOIL(Tensor a, Tensor b){
    Tensor output({0});

    for (int ith = 0; ith < a.data.size(); ith++) {
        Matrix point = a.point(ith);
        for (int jth = 0; jth < b.data.size(); jth++) {
            Matrix other_point = b.point(jth);
            output.add(
                (point + other_point).data,
                a.get(point.data) * b.get(other_point.data)
            );
        }
    }
    return output;
}

Function Function::operator*(Function other){
    remap_me(this, &other);
    alpha = FOIL(alpha, other.alpha);
    beta = FOIL(beta, other.beta);
    return Function(alpha, beta);
}

Function Function::operator+(Function f){
    Function p = (Function(alpha) * Function(f.beta)).plus(Function(beta) * Function(f.alpha));
    Function q = (*this) * f;
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








// change data in matrix to entries instead
// better name? ... idk...


bool has_variables(vector<float> point){
    bool state = false;
    for(int dim = 0; dim < point.size(); dim++){
        if(!(point[dim] == 0.0f)){
            state = true; 
            break;
        }   
    }
    return state;
}

void print_mvp(Tensor alpha, Map<string, int> map, float center, int n){
    bool first_term = true; 
    for(int ith = 0; ith < alpha.data.size(); ith++){
        vector<float> point = alpha.point(ith).data;

        // Non Zero Term
        if(!(alpha.get(point) == 0)){
            if(!first_term){
                cout << " + ";
            } else {
                first_term = false;
            }

            // Output Coefficient
            if(!(alpha.get(point) == 1) || !has_variables(point)){  // Print if not 1, OR if constant term
                cout << fixed << setprecision(n) << alpha.get(point);
            }

            // Output vars
            for(int axis = 0; axis < point.size(); axis++){
                int power = point[axis];
                if(!(power == 0)){
                    cout << map.pre_image(axis);
                    if(!(power == 1)){
                        cout << "^" << power;
                    } 
                } 
            }
        } 
    }
}



void Function::print(int n) {
    std::cout << "alpha: ";
    print_mvp(alpha, map, center, n);
    std::cout << "\n";

    std::cout << "beta:  ";
    print_mvp(beta, map, center, n);
    std::cout << "\n\n";
}













//var map? ... map?... idk... other names?.... idk...





// /**
//  * @returns {Q, R}
//  */
// vector<Function> Function::operator/(Function f){
//     // if f is rational. multiply by recriprecal. 
//     // then divide

//     // syntheic division 
//     if(f.alpha.size() == 2){

//         float R;
//         float C = f.alpha[1]; 
//         f.alpha[0] = f.alpha[0] / f.alpha[1];
//         f.alpha[1] = 1.0f;
//         float value = alpha.back();
//         vector<float> Q(alpha.size() - 1);
//         Q[Q.size() - 1] = value;

//         for(int i = alpha.size() - 2; i >= 0; i--){
//             value *= -f.alpha[0];
//             value += alpha[i];

//             if(i == 0){
//                 R = value; // Remainder
//             } else {
//                 Q[i - 1] = value;
//             }
//         }


//         return {Function(Q) / C, Function({R}, f.alpha) / C};
//     } else { // Long Division
//         vector<float> Q(alpha.size() - f.alpha.size() + 1, 0.0f);
//         Function R = *this; // dividend

//         while(R.deg() >= f.deg()){
//             float c = R.alpha.back() / f.alpha.back();
//             Q[R.deg() - f.deg()] = c;
//             R = R - f * c;
//         }

//         return {Function(Q), Function(R.alpha, f.alpha)};
//     }

//     // returns two functions...
// }






// partial derivative & integerate w/ respect to some variable?...

// float Function::integrate(float a, float b){
//     Function f = *this;
//     f.alpha.push_back(0.0f);
//     for(int i = f.alpha.size() - 1; i > 0; i--){
//         f.alpha[i] = f.alpha[i - 1] / i;
//     }
//     return f.at(b) - f.at(a);
// }

// Function Function::derivative(){
//     vector<float> alpha = {};

//     for(int nth = 1; nth < this->alpha.size(); nth++){
//         alpha.push_back(this->alpha.at(this->alpha.size() - nth - 1) * nth);
//     }

//     return Function(alpha);
// }







// function evulation w/ synth dev? 
// ruffin or horner something like that?...





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














// float Function::deg(){ // or call DEG?...
//     // return (alpha.size() - beta.size());

// }

/// ?.... im not sure..... if htis good or not?... idk....
float Function::deg(int dim){
    return (alpha.shape[dim] - beta.shape[dim]);
}





// calude synth div version...

// float C = f.alpha[1];
//         float R = alpha[0];
//         vector<float> Q(alpha.size() - 1);

//         for(int i = alpha.size() - 1; i > 0; i--){
//             Q[i - 1] = alpha[i];
//             R -= Q[i - 1] * f.alpha[0];
//         }

//         return {Function(Q) / C, Function({R}, f.alpha) / C};




// make own vector class that handles negative indicies in a way?... that way we can better handle the case of negative exponents & stuff....