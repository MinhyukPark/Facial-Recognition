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
 * @brief Performs dot product on two arrays
 * this function will malloc for the user a double
 * arrays must be of same size
 * @return a double
 * @param first array
 * @param second array
 * @param length of arrays
 */
double dot_product(const double* x, const double* y, int length)
{
    double retVal = 0.0;
    for(int i =0;i<length; i++)
    {
        retVal+=x[i] *y[i];
    }
    return retVal;
}

/**
 * @brief Performs vector * matrix
 * this function will malloc for the user a vector*
 * @return a vector*
 * @param vec
 * @param mat
 */
 vector* vecmat_multiply(const vector* vec, const matrix* mat) {
    
    if(vec == NULL  || mat == NULL) {
        return NULL;
    }

    return NULL;
}


 /**
 * @brief Performs  matrix * vector
 * this function will malloc for the user a vector*
 * @return a vector*
 * @param mat
 * @param vec
 */
vector* matvec_multiply(const matrix* mat, const vector* vec)
{
    if(vec == NULL  || mat == NULL) {
        return NULL;
    }
    vector *retVec = vector_create(vec->size);
    for(size_t i =0; i< retVec->size; i++)
    { 
        VEC(retVec,i) = dot_product((double*)((mat->data) + mat->row*i), (double*)vec, vec->size);
    }
    return retVec;
}
