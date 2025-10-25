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
    vector<Entry> entries = {};
    Sparse output(entries);

    for(Entry a : terms.entries){
        for(Entry b : f.terms.entries){
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

vector<Function> Function::operator/(Function f){

}




void Function::operator*=(Function f){
    *this = *this * f;
}

