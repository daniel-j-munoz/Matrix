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
    return (*this) + (other * Q(-1, 1));
}

Sparse Sparse::operator*(Q scale){
    Sparse output = *this;
    for(int i = 0; i < output.entries.size(); i++){
        output.entries[i].value *= scale;
    }
    return output;
}

Sparse Sparse::operator*(int z){
    return *this * Q(z, 1);
}

Sparse Sparse::operator/(Q q){
    q.flip();
    return (*this) * q;
}

Sparse Sparse::operator/(int z){
    return (*this) * Q(1, z);
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

void Sparse::add(vector<int> dim, vector<int> index, Q value){
    add(Entry(dim, index, value));
}




