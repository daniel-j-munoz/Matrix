#include "Entry.h"

Entry::Entry(vector<int> dim, vector<int> index, float value){
    this->dim = dim;
    this->index = index;
    this->value = value;
}

bool Entry::equal(Entry a, Entry b){
    if(a.dim.size() == b.dim.size()){

        bool zero = true;
        for(int i = 0; i < a.dim.size(); i++){
            if(!(a.index[i] == 0 && b.index[i] == 0)){
                zero = false;
            }
        }
        if(zero){
            return true;
        }

        for(int i = 0; i < a.dim.size(); i++){

            bool found = false;
            for(int j = 0; j < b.dim.size(); j++){
                if(a.dim[i] == b.dim[j] && a.index[i] == b.index[j]){
                    found = true;
                }
            }

            if(!found){
                return false;
            }
        }

        return true;
    }
        
    return false;
} 


// matrix instead?... map?...
// method that handles finding if indices are equal?...