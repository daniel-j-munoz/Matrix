#include "Function.h"



Function::Function(Sparse terms){
    this->terms = terms;
}

Function Function::operator+(Function f){
    return Function(terms + f.terms);
}

Function Function::operator-(Function f){
    return Function(terms + (f.terms * -1));
}

Function Function::operator*(Function f){
    
}