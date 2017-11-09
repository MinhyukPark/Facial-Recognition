/**
 * @file linalg.c
 * @authon Minhyuk Park
 * @date 7 Nov 2017
 * @brief File containing common linear algebra functions.
 */
#include <stdlib.h>
#include <stdio.h>

#include "linalg.h"

vector* vector_create(size_t size) {
    if(size <= 0) {
        return NULL;
    }
    vector* retval = malloc((size * sizeof(double)) + sizeof(size_t));
    retval->size = size;
    return retval;
}

matrix* matrix_create(size_t row, size_t col) {
    if(row <= 0 || col <= 0) {
        return NULL;
    }
    matrix* retval =  malloc((row * col * sizeof(double)) + (2 * sizeof(size_t)));
    retval->row = row;
    retval->col = col;
    return retval;
}

/**
 * @brief Performs vector * matrix
 * this function will malloc for the user a matrix*
 * @return a matrix*
 * @param vec
 * @param mat
 */
 matrix* vecmat_multiply(const vector* vec, const matrix* mat) {
    
    if(vec == NULL  || mat == NULL) {
        return NULL;
    }
    
    for(int i = 0; i < 5; i ++) {
        printf("%f\n", vec->data[i]);
    }
    for(int i = 0; i < 25; i ++) {
        printf("%f\n", mat->data[i]);
    }
    return NULL;
}
 