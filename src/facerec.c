#include "linalg.h"
#include <stdio.h>

int main() {
    vector* vec = vector_create(5);
    matrix* mat = matrix_create(5, 5);

    for(int i = 0; i < 5; i ++) {
        vec->data[i] = i;
    }

    for(int i = 0; i < 25; i ++) {
        mat->data[i] = i;
    }
    


    vector* vec_result = vecmat_multiply(vec, mat);
    printf("%p", vec_result);
    printf("%f", MAT(mat, 0, 0));
    printf("%f", VEC(vec, 0));
    return 0;
}