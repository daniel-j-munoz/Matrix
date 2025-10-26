#include "Q.h"

#include <iostream> 
using namespace std;

Q::Q(int alpha, int beta){
    int GCD = gcd(alpha, beta);
    this->alpha = alpha / GCD;
    this->beta = beta / GCD;
}

Q Q::operator+(Q q){
    Q output = *this;
    int LCM = lcm(beta, q.beta); 
    output.alpha = alpha * (LCM / beta) + q.alpha * (LCM / q.beta); 
    output.beta = LCM;
    return output;
}

Q Q::operator-(Q q){
    q = q * -1;
    return *this + q;
}   

Q Q::operator*(Q q){
    Q copy = *this;
    copy.alpha = alpha * q.alpha;
    copy.beta = beta * q.beta; 
    return copy;
}

Q Q::operator/(Q q){
    q.flip();
    return *this * q;
}

void Q::operator+=(Q q){
    Q output = *this + q;
    alpha = output.alpha;
    beta = output.beta;
}

void Q::operator-=(Q q){
    Q output = *this - q;
    alpha = output.alpha;
    beta = output.beta;
}

void Q::operator*=(Q q){
    Q output = *this * q;
    alpha = output.alpha;
    beta = output.beta;
}

Q Q::operator^(int z){
    if(z == 0){
        return Q(1, 1);
    } 

    if(z < 0){
        z *= -1;
        flip();
    }

    Q output = *this;
    for(int i = 0; i < z - 1; i++){
        output = output * (*this);
    }
    return output;
}

Q Q::operator*(int z){
    Q copy = *this;
    copy.alpha *= z;
    return copy;
}

Q Q::operator/(int z){
    Q copy = *this;
    copy.beta *= z;
}





void Q::print(){
    cout << to_string(alpha) << "/" << to_string(beta) << "\n\n";
}

void Q::flip(){
    int temp = alpha;
    alpha = beta;
    beta = temp;
}


int Q::gcd(int a, int b){
    while (!(b == 0)) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int Q::lcm(int a, int b){
    return (a * b) / gcd(a, b);
}

// i guess you could have another class that handles integers no ratios and stuff
//  but will do it like this for now....



// equality checking 
bool Q::operator==(Q q){
    if(alpha == q.alpha && beta == q.beta){
        return true;
    } else {
        return false;
    }
}