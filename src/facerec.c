#include "linalg.h"
#include <stdio.h>

int main() {
    vector* vec = malloc(sizeof(size_t) + (5 * sizeof(double)));
    vec->size = 5;
    for(int i = 0; i < 5; i ++) {
        vec->data[i] = i;
    }

    matrix* mat = malloc((2 * sizeof(size_t)) + (25 * sizeof(double)));
    mat->row = 5;
    mat->col = 5;

    for(int i = 0; i < 25; i ++) {
        mat->data[i] = i;
    }
    


    double** mat_result = vecmat_multiply(vec, mat);
    printf("%p", mat_result);
    return 0;
}