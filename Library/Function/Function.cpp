#include "Function.h"


// get rid of sparse?.....
// and just handle function as if it was like a sparse tensor?....
// or no...?...
// having sparse tensor is good generalization?.....
// idk......



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
    // vector<Entry> entries = {};
    // Sparse output(entries);

    // for(Entry a : terms.entries){
    //     for(Entry b : f.terms.entries){
    //         vector<int> dim = a.dim;
    //         vector<int> index = a.index;
    //         for(int i = 0; i < b.dim.size(); i++){
    //             // Search
    //             bool found = false;
    //             for(int j = 0; j < dim.size(); j++){
    //                 if(b.dim[i] == dim[j]){
    //                     index[j] += b.index[i];
    //                     found = true;
    //                 }
    //             }
    //             if(!found){
    //                 dim.push_back(b.dim[i]);
    //                 index.push_back(b.index[i]);
    //             }
    //         }
    //         output.add(Entry(dim, index, a.value * b.value));
    //     }
    // }
    // return output;


    Function output();

    for(int i = 0; i < terms.numbers.size(); i++){
        for(int j = 0; j < f.terms.numbers.size(); j++){

            // multiply terms... multiply term function?...
            Function prod = monomial_product();
            output += prod;

        }
    }
}


int index_of(vector<int> list, int x){
    for(int i : list){
        if(list[i] == x){
            return i;
        }
    }
    return -1;
}


Function Function::monomial_product(vector<int> shell, vector<int> point, Q number, vector<int> next_shell, vector<int> next_point, Q next_number){
    for(int i = 0; i < next_shell.size(); i++){
        int index = index_of(shell, next_shell[i]); 
        if(index == -1){
            shell.push_back(next_shell[i]);
            point.push_back(next_point[i]);
        } else {
            point[i] += next_point[i];
        }
    }

    number *= next_number;

    return Function(Sparse({shell}, {point}, {number}));
}

vector<Function> Function::operator/(Function f){

    // long diviosn....

    // you have to group & stuf...

   
    
}






vector<Function> Function::group(int dim){
    // for(int i = 0; i < terms.entries.size(); i++){
    //     if(terms.entries[i].)
    // }

    vector<Function> output = {};

    for(Entry entry : terms.entries){


        int index = index_of(entry, dim);
        for(int i = 0; i < entry.dim.size(); i++){
            if(!(i == index)){
                entry.dim[i];
                entry.index[i];
            }
        }

    }
}

void Function::operator+=(Function f){
    *this = *this + f;
}

void Function::operator*=(Function f){
    *this = *this * f;
}





// long division?....
//  Function Q();
//     Function R = *this; // dividend

//     while(R.deg() >= deg()){
//         float c = R.alpha.back() / f.alpha.back();
//         Q[R.deg() - f.deg()] = c;
//         R = R - f * c;
//     }

//     return {Function(Q), Function(R.alpha, f.alpha)};