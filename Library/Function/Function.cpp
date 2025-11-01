#include "Function.h"


Function::Function(vector<Monomial> monomials){
    this->monomials = monomials;
    // lexisort in here?...
}

Function Function::operator+(Function other){
    Function copy = *this;
    for(Monomial m : other.monomials){
        copy += m;
    }
    return copy;
}

Function Function::operator+(Monomial other){
    Function copy = *this;
    for(int i = 0; i < copy.monomials.size(); i++){
        if(copy.monomials[i].like_terms(other)){
            copy.monomials[i].number += other.number;
            return copy;
        }
    }

    copy.monomials.push_back(other);
    // lexisort here?...
    copy.lexisort();
    return copy;
}


Function Function::operator-(Function other){
    return *this + (other * -1);
}

Function Function::operator*(int x){
    Function copy = *this;
    for(int i = 0; i < copy.monomials.size(); i++){
        copy.monomials[i] = copy.monomials[i] * x;
    }
    return copy;
}

Function Function::operator*(Function other){
    Function c({});
    for(Monomial a : monomials){
        for(Monomial b : other.monomials){
            c += (a * b);
        }
    }
    return c;
}

vector<Function> Function::operator/(Function divisor){
    Function Q({}); 
    Function R({}); 
    Function remainder = *this;

    while(remainder.monomials.size() > 0){
        Monomial a = remainder.lm(); 
        Monomial b = divisor.lm();

        if(b.divides(a)){
            Monomial q = a / b; 
            Q += q;
            remainder -= divisor * q;
            remainder.lexisort();
        } else {
            R += a;
            remainder.monomials.pop_back();
        }
    }

    return {Q, R};
}

bool compare(Monomial& a, Monomial& b){ // const as well?... or no....?...
    a.form();
    b.form();

    if(!(a.constant() && b.constant())){
        for (int i = 0; i < a.shell.size(); ++i) {
            if (!(a.shell[i] == b.shell[i])) {
                return a.shell[i] < b.shell[i];
            }

            if (!(a.point[i] == b.point[i])) {
                return a.point[i] < b.point[i];
            }
        }
    }
    
    return false; 
}

void Function::lexisort(){
    
    std::sort(monomials.begin(), monomials.end(), compare);
}

Monomial Function::lm(){
    // assume in lexiographic order first...
    return monomials.back();
}

















int Function::max_deg(int dim){
    int maximum = std::numeric_limits<int>::lowest();
    for(Monomial m : monomials){
        maximum = max(maximum, m.deg(dim));
    }
}

int Function::min_deg(int dim){
    int minimum = std::numeric_limits<int>::max();
    for(Monomial m : monomials){
        minimum = min(minimum, m.deg(dim));
    }
}

vector<Function> Function::group(int dim){
    vector<Function> coefficents(max_deg(dim) - min_deg(dim) + 1, Function({})); 
    for(int i = 0; i < coefficents.size(); i++){
        coefficents[i].wrt = dim;
        coefficents[i].power = i + min_deg(dim);
    }

    for(Monomial m : monomials){
        int index = m.deg(dim);
        coefficents[index] += m.coefficent(dim);
    }
    return coefficents;
}

void Function::operator+=(Function f){
    *this = *this + f;
}

void Function::operator-=(Function f){
    *this = *this - f;
}

void Function::operator*=(Function f){
    *this = *this * f;
}






void Function::operator+=(Monomial other){
    *this = *this + other;
}

Function Function::operator*(Monomial other){
    return *this * Function({other});
}




// Function Function::gcf(Function other){

//     Function a = *this;
//     Function b = other;
//     Function remainder({});

//     while(!b.is_constant()){
//         remainder = (a / b)[1];  // Get remainder
//         a = b;
//         b = remainder;
//     }

//     if(b.monomials[0].number == 0){
//         return a;
//     } else {
//         return Function({Monomial({0}, {0}, 1)}); // coprime
//     }
// }

// Function Function::lcm(Function other){
//     return ((*this * other) / this->gcf(other))[0];
// }





// check if constant function?....









vector<string> my_alphabet = { // no i or e    
    "a", "b", "c", "d", "f", 
    "g", "h", "j", "k", "l", 
    "m", "n", "o", "p", "q",
    "r", "s", "t", "u", "v", 
    "w", "x", "y", "z", "A", 
    "B", "C", "D", "E", "F", 
    "G", "H", "I", "J", "K", 
    "L", "M", "N", "O", "P",
    "Q", "R", "S", "T", "U", 
    "V", "W", "X", "Y", "Z"
};

int digits(int number){
    if(number == 0){
        return 1;
    }

    if(number < 0){
        number *= -1;
    }

    int size = 0;
    while(number > 0){
        number /= 10;
        size++;
    }
    return size;
}

void Function::print(){
    string s = "";
    for(int i = 0; i < monomials.size(); i++){
        Monomial monomial = monomials[i];
        int number = monomial.number;

        if(!(number == 0)){

            if(i == 0){
                if(number < 0){
                    s += "-";
                }
            } else {
                if(number > 0){
                    s += " + ";
                } else {
                    s += " - ";
                }
            }

            if(!(number == 1) || monomial.constant()){
                s += to_string(abs(number)); 
            }
            
            for(int j = 0; j < monomial.shell.size(); j++){
                int power = monomial.point[j];
                if(!(power == 0)){
                    s += my_alphabet[monomial.shell[j]];
                    if(!(power == 1)){
                        s += "^";
                        if(digits(power) > 1){
                            s += "(";
                            s += to_string(power);
                            s += ")";
                        } else {
                            s += to_string(power);
                        }
                    }
                }
            }
        }
    }
    cout << s << "\n\n";

}


