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

//! macro for element access in a matrix struct
#define MAT(m, x, y) (m->data[(x * m->col) + y])
//! macro for element access in a vector struct
#define VEC(v, x) (v->data[x])

/**
 * @brief represents a vector
 * padding is to make sure that matrix and vector
 * both have the same byte size and allignment
 * between matrix and vector they are able to be casted into one another
 */
typedef struct _vector {
    //! the number of elements in the vector
    size_t size;
    //! unused value but important as padding
    size_t padding;
    //! the elements of the vector
    double data[];
} vector;

/**
 * @brief represents a matrix
 * between matrix and vector they are able to be casted into one another
 */
typedef struct _matrix {
    //! the number of rows in the matrix
    size_t row;
    //! the number of columns in the matrix
    size_t col;
    //! row wise expansion of the elements in the matrix
    double data[];
} matrix;


/**
 * @brief Creates a vector
 * this function will malloc the exact space for the required dimensions
 * @return vector* the newly malloced vector
 * @param size size_t the desired number of elements in the vecrtor
 */
vector* vector_create(size_t size);

/**
 * @brief Creates a matrix
 * this function will malloc the exact space for the required dimensions
 * @return matrix* the newly malloced matrix
 * @param row size_t the desired number of rows in the matrix
 * @param col size_t the desired number of columns in the matrix
 */
matrix* matrix_create(size_t row, size_t col);

/**
 * @brief Converts vector into matrix
 * this function will "cast" the vector into a matrix
 * by using the fact that they both have the same size.
 * when calling this function, calling free() on the matrix
 * will free the vector and vice versa.
 * @return matrix* the new pointer for input vector*
 * @param vec vector* to be converted
 * @param orientation int 1 is Row-wise and 0 is Column-wise
 * in terms of the newly formed matrix
 */
matrix* vec_to_mat(vector* vec, int orientation);

/**
 * @brief Reshapes the matrix
 * this function will reshape the matrix in constant time
 * @param mat matrix* to be reshaped
 * @param row size_t the new row
 * @param col size_t the new column
 */
void matrix_reshape(matrix* mat, size_t row, size_t col);

/**
 * @brief Performs dot product on two double*
 * this function will malloc for the user a double
 * arrays must be of same size
 * @return a double representing the inner product
 * @param x const double* the first vector
 * @param y const double* the second vector
 * @param length int the size of the vectors
 */
double dot_product(const double* x, const double* y, int length);

 /**
 * @brief Performs vector matrix multiplication
 * this function will malloc for the user a vector*
 * if the vector is of size M and the matrix size M by N,  
 * the resulting column vector will be of size N
 * @return vector* newly malloced result of vector matrix multiplication
 * @param vec const vector* the input vector
 * @param mat const matrix* the input matrix
 */
 vector* vecmat_multiply(const vector* vec, const matrix* mat);

 /**
 * @brief Performs  matrix vector multiplication
 * this function will malloc for the user a vector*
 * if the matrix is of size M by N and the vector N,
 * the resulting row vector will be of size M
 * @return vector* newly malloced result of matrix vector multiplication
 * @param mat const matrix* the input matrix
 * @param vec const vector* the input vector
 */
vector* matvec_multiply(const matrix* mat, const vector* vec);

/**
 * @brief prints the matrix
 * this function will not modify the matrix and print to stdout
 * @param mat const matrix* the matrix to be printed
 */
void mat_print(const matrix* mat);

/**
 * @brief prints the vector
 * this function will not modify the vector and print to stdout
 * @param vec const vector* the vector to be printed
 */
void vec_print (const vector* vec);

 /**
 * @brief Performs standard matrix multiplication
 * this function will malloc for the user a matrix*
 * @return matrix* newly malloced result of mat_a times mat_b
 * @param mat_a const matrix* the matrix to be multiplied to
 * @param mat_b const matrix* the matrix to be multiplied
 */
matrix* matmat_multiply(const matrix* mat_a, const matrix* mat_b);

 /**
 * @brief Performs standard matrix addition
 * this function will malloc for the user a matrix*
 * @return matrix* newly malloced result of mat_a plus mat_b
 * @param mat_a const matrix* the matrix to be added to
 * @param mat_b const matrix* the matrix to be added
 */
matrix* matmat_addition(const matrix* mat_a, const matrix* mat_b);

 /**
 * @brief Performs standard matrix subtration
 * this function will malloc for the user a matrix*
 * @return matrix* newly malloced result of mat_a minus mat_b
 * @param mat_a const matrix* the matrix to be subtracted from
 * @param mat_b const matrix* the matrix to be subtrated
 */
matrix* matmat_subtraction(const matrix* mat_a, const matrix* mat_b);

 /**
 * @brief Performs  scalar multiplication of a matrix
 * this function will malloc for the user a matrix*
 * @return matrix* that is the result of element wise multiplication of the
 * matrix by the scalar
 * @param mat const matrix* the input matrix
 * @param scalar const double the input scalar
 */
matrix* matscalar_multiply(const matrix* mat_a, const double scalar);

 /**
 * @brief Performs scalar division of a matrix
 * this function will malloc for the user a matrix*
 * @return matrix* that is the result of element wise division of the matrix 
 * by the scalar
 * @param mat const matrix* the input matrix 
 * @param scalar const double the input scalar
 */
matrix* matscalar_divide(const matrix* mat, const double scalar);

 /**
 * @brief Performs matrix transpose
 * this function will malloc for the user a matrix*
 * @return matrix* the newly transposed and malloced matrix
 * @param mat const matrix*  the matrix to be transposed
 */
matrix* mat_transpose(const matrix* mat);

 /**
 * @brief Appends vector b to vector a
 * this function will realloc for the user vector a
 * and free vector b
 * @param vec_a vector** the vector to be realloced
 * @param vec_b vector* the vector to be appended and freed thereafter
 */
void vec_append(vector** vec_a, vector* vec_b);

/**
 * @brief Performs Jacobi eigenvalue iteration
 * this function will required the user to pass in non-null it_num and rot_num
 * it does not malloc but rather requires the caller to malloc space for it
 * @param N int the dimiension of the input matrix a, which is a N by N matrix
 * @param a[] double[] the input matrix which has to be square, real, and symmetric
 * @param it_max int maximum number of iterations to stop at
 * @param v[] double[]output matrix of eigenvectors, which is a N by N matrix
 * @param d[] double[] output matrix of eigenvalues, in descending order
 * @param it_num int* output total number of iterations
 * @param rot_num int* output total number of rotations
*/
void eigen(int N, double a[], int it_max, double v[], double d[], int* it_num, int* rot_num);

/**
 * @brief modifies a matrix to be the identity matrix of size n
 * @param n int the dimension
 * @param a[] double output identity matrix
 */
void mat_identity(int n, double a[]);

/**
 * @brief gets the diagonal entries
 * @param n int the dimension
 * @param a[] double[] input the matrix, N by N
 * @param v[] double[] output the diagonal entries, N
 */
void diag_vector(int n, double a[], double v[]);

/**
 * @brief computes the Frobenius norm in a right eigensystem
 * @return double the frobenius norm of A * X - X * lambda
 * @param n int the dimension of the matrix
 * @param k int the number of eigen vectors
 * @param a[] double[] input matrix of size n by n
 * @param x[] double[] input vector of eigenvectors of size k
 * @param lamdba[] double[] input vector of eigen values
 */
double frobenius_norm(int n, int k, double a[], double x[], double lambda[]);

/**
 * @brief computes the variance covariance matrix
 * @return matrix* the output variance-covariance matrix 
 * this function will malloc a new matrix
 * @param mat a matrix* representing the input matrix of deviation scores of size n by k 
 */
matrix* covmat(matrix* mat);

/**
 * @brief computes the average matrix of all the *vector images
 * @return matrix* the average matrix
 * @param images vector* a vector of all images to average
 * @param num_images int number of images in the vector 
 */
matrix * compute_average(vector* images, int num_images);



