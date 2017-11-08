/**
 * @file linalg.c
 * @authon Minhyuk Park
 * @date 7 Nov 2017
 * @brief File containing common linear algebra functions.
 */
#include <stdlib.h>
#include <stdio.h>

#include "linalg.h"

/**
 * @brief Performs vector * matrix
 * this function will malloc for the user a matrix*
 * @return a matrix*
 * @param vec
 * @param mat
 */
 double** vecmat_multiply(const vector* vec, const matrix* mat) {
    
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
 