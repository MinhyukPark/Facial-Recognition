#include "linalg.h"
#include <stdio.h>

int main() {
    vector* vec = vector_create(5);
    matrix* mat = matrix_create(5, 5);

    for(int i = 0; i < 5; i ++) {
        vec->data[i] = 2;
    }

    for(int i = 0; i < 25; i ++) {
        mat->data[i] = 1;
    }
    


    vector* vec_result = vecmat_multiply(vec, mat);
    //printf("%p", vec_result);
    //printf("%f", MAT(mat, 0, 0));
    //printf("%f", VEC(vec, 0));

    vec_result = matvec_multiply(mat,vec);
    for(int i = 0; i < 5; i ++) {
        printf("%f\n",vec_result->data[i]);
    }
    return 0;
}