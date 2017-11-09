/**
 * @file linalg.h
 * @authon Minhyuk Park
 * @date 7 Nov 2017
 * @brief File containing common linear algebra functions.
 */
#pragma once

#include <stdlib.h>

#define MAT(m, x, y) (m->data[(x * m->row) + y])
#define VEC(v, x) (v->data[x])

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
 * @brief Performs dot product on two arrays
 * this function will malloc for the user a double
 * arrays must be of same size
 * @return a double
 * @param first array
 * @param second array
 * @param length of arrays
 */
double dot_product(const double* x, const double* y, int length);

/**
 * @brief Performs vector * matrix
 * this function will malloc for the user a vector*
 * @return a vector*
 * @param vec
 * @param mat
 */
 vector* vecmat_multiply(const vector* vec, const matrix* mat);




 /**
 * @brief Performs  matrix * vector
 * this function will malloc for the user a vector*
 * @return a vector*
 * @param mat
 * @param vec
 */
vector* matvec_multiply(const matrix* mat, const vector* vec);
