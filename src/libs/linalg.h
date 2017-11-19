/**
 * @file linalg.h
 * @authon Minhyuk Park
 * @date 7 Nov 2017
 * @brief File containing common linear algebra functions.
 */
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

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

 /**
 * @brief Performs  matrixA * matrixB
 * this function will malloc for the user a matrix*
 * @return a matrix*
 * @param matA
 * @param matB
 */
matrix* matmat_multiply(const matrix* matA, const matrix* matB);

 /**
 * @brief Performs  matrixA + matrixB
 * this function will malloc for the user a matrix*
 * @return a matrix*
 * @param matA
 * @param matB
 */
matrix* matmat_addition(const matrix* matA, const matrix* matB);

 /**
 * @brief Performs  matrixA - matrixB
 * this function will malloc for the user a matrix*
 * @return a matrix*
 * @param matA
 * @param matB
 */
matrix* matmat_subtraction(const matrix* matA, const matrix* matB);

 /**
 * @brief Performs  matrixA * scaler
 * this function will malloc for the user a matrix*
 * @return a matrix*
 * @param matA
 * @param scalar
 */
matrix* matscalar_multiply(const matrix* matA, const double scalar);

 /**
 * @brief Performs  matrixA / scaler
 * this function will malloc for the user a matrix*
 * @return a matrix*
 * @param matA
 * @param scalar
 */
matrix* matscalar_divide(const matrix* matA, const double scalar);

 /**
 * @brief Performs  transpose(mat)
 * this function will malloc for the user a matrix*
 * @return a matrix*
 * @param matA
 */
matrix* mat_transpose(const matrix* mat);

 /**
 * @brief Performs  vec = vecA+vecB
 * this function will malloc for the user a vector*
 * and destroys vecA and vecB
 * @return void
 * @param vecA
 * @param vecB
 */
void vec_append(vector** vecA, vector* vecB);

/**
 * @brief Performs Jacobi eigenvalue iteration
 * this function will 
 * @param N the dimiension of the input matrix a, which is a N by N matrix
 * @param a[] the input matrix which has to be square, real, and symmetric
 * @param it_max maximum number of iterations to stop at
 * @param v[] output matrix of eigenvectors, which is a N by N matrix
 * @param d[] output matrix of eigenvalues, in descending order
 * @param it_num output total number of iterations
 * @param rot_num output total number of rotations
*/
void eigen(int N, double a[], int it_max, double v[], double d[], int* it_num, int* rot_num);

/**
 * @brief returns an identity matrix of size n
 * @param n the dimension
 * @param a[] output identity matrix
 */
void mat_identity(int n, double a[]);

/**
 * @brief gets the diagonal entries
 * @param n the dimension
 * @param a[] input the matrix, N by N
 * @param v[] output the diagonal entries, N
 */
void diag_vector(int n, double a[], double v[]);



/**
 * @brief computes the Frobenius norm in a right eigensystem
 * @param n the dimension of the matrix
 * @param k the number of eigen vectors
 * @param a[] input matrix of size n by n
 * @param x[] input vector of eigenvectors of size k
 * @param lamdba[] input vector of eigen values
 * @return double the frobenius norm of A * X - X * lambda
 */
double frobenius_norm(int n, int k, double a[], double x[], double lambda[]);


/**
 * @brief computes the average matrix of all the tiff images
 * @return matrix* the average matrix 
 */
matrix * compute_average();
