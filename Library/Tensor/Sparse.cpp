#include "Sparse.h"

Sparse::Sparse(){

}

Sparse::Sparse(vector<Entry> entries){
    this->entries = entries;
}

Sparse Sparse::operator+(Sparse other){
    Sparse output = *this;
    for(Entry entry : other.entries){
        output.add(entry);
    }
    return output;
}

Sparse Sparse::operator-(Sparse other){
    return (*this) + (other * -1.0f);
}

Sparse Sparse::operator*(float scale){
    Sparse output = *this;
    for(int i = 0; i < output.entries.size(); i++){
        output.entries[i].value *= scale;
    }
    return output;
}

Sparse Sparse::operator/(float scale){
    return (*this) * (1.0f / scale);
}


void Sparse::add(Entry entry){
    for(int i = 0; i < entries.size(); i++){
        if(Entry::equal(entries[i], entry)){
            entries[i].value += entry.value;
            return;
        } 
    }

    entries.push_back(entry);
}

void Sparse::add(vector<int> dim, vector<int> index, float value){
    add(Entry(dim, index, value));
}






// division...?...
// tensor product?...
// contraction?..
// foiling?...
// inverse?...
// get?...
// shape is a bit more dynamic now...
// subspace?...
