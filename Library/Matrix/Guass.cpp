#include "Guass.h"

// elementray row operations.

void Guass::swap_row(int a, int b, Matrix* A){
    for(int n = 0; n < A->N; n++){
        float past = A->get(b, n); 
        A->set(b, n, A->get(a, n)); 
        A->set(a, n, past);
    }
}

void Guass::swap_col(int a, int b, Matrix* A){
    for(int m = 0; m < A->M; m++){
        float past = A->get(m, b); 
        A->set(m, b, A->get(m, a)); 
        A->set(m, a, past);
    }
}

void Guass::scale_row(int m, float scale, Matrix* A){
    for(int n = 0; n < A->N; n++){
        A->set(m, n, A->get(m, n) * scale);
    }
}


/**
 * e.g. row_a + scale * row_b **/
void Guass::row_plus(int a, float scale, int b, Matrix* A){
    for(int i = 0; i < A->N; i++){
        A->set(a, i, A->get(a, i) + scale * A->get(b, i));
    }
}

// col plus
