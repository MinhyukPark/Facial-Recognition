/**
 * @file linalg.h
 * @authon Minhyuk Park
 * @date 7 Nov 2017
 * @brief File containing common linear algebra functions.
 */
#pragma once

#include <stdlib.h>

#define MAT(m, x, y) (m->data[(x * m->col) + y])
#define VEC(v, x) (v->data[x])

typedef struct _vector {
    size_t size;
    size_t padding;
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
 * @brief Converts vector into matrix
 * this function will "cast" the vector into a matrix
 * by using the fact that they both have the same size.
 * when calling this function, calling free() on the matrix
 * will free the vector and vice versa.
 * @return a matrix*
 * @param vector* to be converted
 * @param int orientation where 1 is Row-wise and 0 is Column-wise
 */
matrix* vec_to_mat(vector* vec, int orientation);

/**
 * @brief Reshapes the matrix
 * this function will reshape the matrix in constant time
 * @param matrix* to be reshaped
 * @param size_t row for the new row
 * @param size_t col for the new column
 */
void matrix_reshape(matrix* mat, size_t row, size_t col);

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

/**
 * @brief prints the matrix
 * this function will not modify the matrix and print to stdout
 * @param mat the matrix to be printed
 */
void mat_print(const matrix* mat);

/**
 * @brief prints the vector
 * this function will not modify the vector and print to stdout
 * @param vec the vector to be printed
 */
void vec_print (const vector* vec);

