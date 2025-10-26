#include "Monomial.h"


Monomial::Monomial(vector<int> shell, vector<int> point, int number){
    this->shell = shell;
    this->point = point;
    this->number = number;
}




int index_of(vector<int> list, int x){
    for(int i = 0; i < list.size(); i++){
        if(list[i] == x){
            return i;
        }
    }
    return -1;
}


Monomial Monomial::operator*(int x){
    Monomial copy = *this;
    copy.number *= x;
    return copy;
}


Monomial Monomial::operator*=(int x){
    *this = *this * x;
}

Monomial Monomial::operator*(Monomial other){
    Monomial copy = *this;

    for(int i = 0; i < other.shell.size(); i++){
        int index = index_of(shell, other.shell[i]); 
        if(index == -1){
            copy.shell.push_back(other.shell[i]);
            copy.point.push_back(other.point[i]);
        } else {
            copy.point[i] += other.point[i];
        }
    }

    copy.number *= other.number;
    return copy;
}

Monomial Monomial::operator/(Monomial other){
    Monomial copy = *this;
    for(int i = 0; i < other.shell.size(); i++){

        bool found = false;
        for(int j = 0; j < shell.size(); j++){
            if(other.shell[i] == shell[i]){
                found = true;
                copy.point[i] -= other.point[i];
            }
        }

        if(!found){
            copy.shell.push_back(other.shell[i]);
            copy.point.push_back(-other.point[i]);
        }
    }

    return copy;
}



// sort wrt to shell? also w/ point?...
void Monomial::sort(){
    vector<int> index(shell.size());
    for (int i = 0; i < index.size(); i++){
        index[i] = i;
    }

    std::sort(index.begin(), index.end(), [&](int i, int j) {
        return shell[i] < shell[j];
    });

    vector<int> new_point = {};
    vector<int> new_shell = {};
    for(int i : index) {
        new_point.push_back(point[i]);
        new_shell.push_back(shell[i]);
    }

    shell = new_shell;
    point = new_point;
}


void Monomial::remove_zeros(){
    if(shell.size() > 1){
        for (int i = point.size() - 1; i >= 0; i--) {
            if (point[i] == 0) {
                shell.erase(shell.begin() + i);
                point.erase(point.begin() + i);
            }
        }
    }
}

// canonical form?.. other names?...
void Monomial::form(){
    sort();
    remove_zeros();
}

bool Monomial::constant(){
    for(int i : point){
        if(!(i == 0)){
            return false;
        }
    }
    return true;
}


// ?....
bool Monomial::operator==(Monomial other){
    if(like_terms(other) && number == other.number){
        return true;
    } else {
        return false;
    }
}

bool Monomial::like_terms(Monomial other){
    if(shell.size() == other.shell.size()){
        form();
        other.form();
        if(
            (constant() && other.constant()) || 
            shell == other.shell && point == other.point
        ){
            return true;
        }
    } else {
        return false;
    }
}





int Monomial::deg(int dim){
    for(int i = 0; i < shell.size(); i++){
        if(shell[i] == dim){
            return point[i];
        }
    }
    return -1;
}

Monomial Monomial::coefficent(int dim){
    Monomial copy = *this;
    if(shell.size() > 1){
        for (int i = shell.size() - 1; i >= 0; i--) {
            if (shell[i] == dim) {
                copy.shell.erase(shell.begin() + i);
                copy.point.erase(point.begin() + i);
            }
        }
    }
    return copy;
}



bool Monomial::divides(Monomial other){
    form(); // forms should be done in constructor and add monomial method before?....... idk......
    other.form();

    if(other.number % number == 0){
        for(int i = 0; i < shell.size(); i++){
            bool found = false;
            for(int j = 0; j < other.shell.size(); j++){
                if(shell[i] == other.shell[i]){
                    bool found = true;
                    if(point[i] - other.point[i] < 0){
                        return false;
                    }
                } 
            }

            if(!found){
                if(-other.point[i] < 0){
                    return false;
                }
            }

        }
        return true;
    } else {
        return false;
    }
}
