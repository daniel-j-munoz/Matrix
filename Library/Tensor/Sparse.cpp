#include "Sparse.h"

// #include <algorithm>

Sparse::Sparse(){

}

Sparse::Sparse(vector<vector<int>> shells, vector<vector<int>> points, vector<Q> numbers){
    this->shells = shells;
    this->points = points;
    this->numbers = numbers;
}

Sparse Sparse::operator+(Sparse other){
    Sparse output = *this;
    for(int i = 0; i < numbers.size(); i++){
        output.add(shells[i], points[i], numbers[i]);
    }
    return output;
}

Sparse Sparse::operator-(Sparse other){
    return (*this) + (other * Q(-1, 1));
}

Sparse Sparse::operator*(Q scale){
    Sparse copy = *this;
    for(int i = 0; i < copy.numbers.size(); i++){
        copy.numbers[i] *= scale;
    }
    return copy;
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

void Sparse::add(vector<int> shell, vector<int> point, Q number){
    for(int i = 0; i < numbers.size(); i++){
        if(equal(&shells[i], &points[i], &shell, &point)){
            numbers[i] += number;
            return;
        }
    }

    shells.push_back(shell);
    points.push_back(point);
    numbers.push_back(number);
}








/**
 * sort wrt to b 
 */
void Sparse::sort(vector<int>* a, vector<int>* b){
    vector<int> index(b->size());
    for (int i = 0; i < index.size(); i++){
        index[i] = i;
    }

    std::sort(index.begin(), index.end(), [&](int i, int j) {
        return b[i] < b[j];
    });

    vector<int> new_a = {};
    vector<int> new_b = {};
    for(int i : index) {
        new_a.push_back(a->at(i));
        new_b.push_back(b->at(i));
    }

    *a = new_a;
    *b = new_a;
}


void Sparse::remove_zeros(vector<int>* shell, vector<int>* point){
    if(shell->size() > 1){
        for (int i = point->size() - 1; i >= 0; i--) {
            if (point->at(i) == 0) {
                shell->erase(shell->begin() + i);
                point->erase(point->begin() + i);
            }
        }
    }
}

// canonical form?.. other names?...
void Sparse::form(vector<int>* shell, vector<int>* point){
    sort(shell, point);
    remove_zeros(shell, point);
}

bool Sparse::origin(vector<int> shell){
    for(int i : shell){
        if(!(i == 0)){
            return false;
        }
    }
    return true;
}

bool Sparse::equal(vector<int>* shell, vector<int>* point, vector<int>* next_shell, vector<int>* next_point){
    if(shell->size() == next_shell->size()){
        form(shell, point);
        form(next_shell, next_point);
        if(
            (origin(*shell) && origin(*next_shell)) || 
            shell == next_shell && point == next_point
        ){
            return true;
        }
    } else {
        return false;
    }
}

