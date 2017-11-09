/**
 * @file linalg.h
 * @authon Minhyuk Park
 * @date 7 Nov 2017
 * @brief File containing common linear algebra functions.
 */
#pragma once

#include <stdlib.h>


typedef struct _vector {
    size_t size;
    double data[];
} vector;

typedef struct _matrix {
    size_t row;
    size_t col;
    double data[];
} matrix;


vector* vector_create(size_t size);

matrix* matrix_create(size_t row, size_t col);



/**
 * @brief Performs vector * matrix
 * this function will malloc for the user a matrix*
 * @return a matrix*
 * @param vec
 * @param mat
 */
 matrix* vecmat_multiply(const vector* vec, const matrix* mat);




 