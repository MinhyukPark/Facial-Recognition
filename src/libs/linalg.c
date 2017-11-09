/**
 * @file linalg.c
 * @authon Minhyuk Park
 * @date 7 Nov 2017
 * @brief File containing common linear algebra functions.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linalg.h"


vector* vector_create(size_t size) {
    if(size <= 0) {
        return NULL;
    }
    vector* retval = malloc((size * sizeof(double)) + (2 * sizeof(size_t)));
    retval->size = size;
    retval->padding  = 0;
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
 * @brief Converts vector into matrix
 * this function will "cast" the vector into a matrix
 * by using the fact that they both have the same size.
 * when calling this function, calling free() on the matrix
 * will free the vector and vice versa.
 * @return a matrix*
 * @param vector* to be converted
 * @param int orientation where 1 is Row-wise and 0 is Column-wise
 */
matrix* vec_to_mat(vector* vec, int orientation) {
    if(orientation == 1) {
        vec->padding = vec->size;
        vec->size = 1;
    } else {
        vec->padding = 1;
    }
    return (matrix*)vec;
}

/**
 * @brief Reshapes the matrix
 * this function will reshape the matrix in constant time
 * @param matrix* to be reshaped
 * @param size_t row for the new row
 * @param size_t col for the new column
 */
void matrix_reshape(matrix* mat, size_t row, size_t col) {
    mat->row = row;
    mat->col = col;
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
        retVal+=(x[i] *y[i]);
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
    vector* retvec = vector_create(vec->size);
    memset(retvec->data, 0, sizeof(double) * vec->size);
    for(size_t j = 0; j < mat->col; j ++) {
        for(size_t i = 0; i < mat->row; i ++) {
            VEC(retvec, j) += (VEC(vec, i) * MAT(mat, i, j));
        }
    }
    return retvec;
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
        VEC(retVec,i) = dot_product(((double*)(mat->data) + (mat->col * i)), (double*)vec->data, vec->size);
    }
    return retVec;
}

/**
 * @brief prints the matrix
 * this function will not modify the matrix and print to stdout
 * @param mat the matrix to be printed
 */
void mat_print(const matrix* mat) {
    for(size_t i = 0; i < mat->row; i ++) {
        for(size_t j = 0; j < mat->col; j ++) {
            printf("%f, ", MAT(mat, i, j));
        }
        printf("\n");
    }
}

/**
 * @brief prints the vector
 * this function will not modify the vector and print to stdout
 * @param vec the vector to be printed
 */
void vec_print(const vector* vec) {
    for(size_t i = 0; i < vec->size; i ++) {
        // printf("%f, ", VEC(vec, i));
        printf("%f", vec->data[i]);
    }
    printf("\n");
}

 /**
 * @brief Performs  matrixA * matrixB
 * this function will malloc for the user a matrix*
 * @return a matrix*
 * @param matA
 * @param matB
 */
matrix* matmat_multiply(const matrix* matA, const matrix* matB)
{
    matrix *retVal = matrix_create(matA->row, matB->col);
    for(size_t i =0; i<matA->row;i++)
    {
        for(size_t j=0; j<matB->col;j++)
        {
            MAT(retVal,i,j) = 0;
            for(size_t k=0; k<matA->col;k++)
            {
                MAT(retVal,i,j) += MAT(matA,i,k)*MAT(matB,k,j);
            }
        }
    }   
    return retVal;
}

 /**
 * @brief Performs  matrixA + matrixB
 * this function will malloc for the user a matrix*
 * @return a matrix*
 * @param matA
 * @param matB
 */
matrix* matmat_addition(const matrix* matA, const matrix* matB)
{
    matrix *retVal = matrix_create(matA->row, matB->col);
    for (size_t i = 0; i < matA->row; i++)
    {
        for (size_t j = 0; j < matB->col; j++)
        {
            MAT(retVal,i,j) = MAT(matA,i,j) + MAT(matB,i,j);
        }
    }
    return retVal;
}

 /**
 * @brief Performs  matrixA - matrixB
 * this function will malloc for the user a matrix*
 * @return a matrix*
 * @param matA
 * @param matB
 */
matrix* matmat_subtraction(const matrix* matA, const matrix* matB)
{
    matrix *retVal = matrix_create(matA->row, matB->col);
    for (size_t i = 0; i < matA->row; i++)
    {
        for (size_t j = 0; j < matB->col; j++)
        {
            MAT(retVal,i,j) = MAT(matA,i,j) - MAT(matB,i,j);
        }
    }
    return retVal;
}

 /**
 * @brief Performs  matrixA * scaler
 * this function will malloc for the user a matrix*
 * @return a matrix*
 * @param matA
 * @param scalar
 */
matrix* matscalar_multiply(const matrix* matA, const double scalar)
{
    matrix *retVal = matrix_create(matA->row, matA->col);
    for (size_t i = 0; i < matA->row; i++)
    {
        for (size_t j = 0; j < matA->col; j++)
        {
            MAT(retVal,i,j) = MAT(matA,i,j) *scalar;
        }
    }
    return retVal;
}


 /**
 * @brief Performs  matrixA / scaler
 * this function will malloc for the user a matrix*
 * @return a matrix*
 * @param matA
 * @param scalar
 */
matrix* matscalar_divide(const matrix* matA, const double scalar)
{
    matrix *retVal = matrix_create(matA->row, matA->col);
    for (size_t i = 0; i < matA->row; i++)
    {
        for (size_t j = 0; j < matA->col; j++)
        {
            MAT(retVal,i,j) = MAT(matA,i,j) /scalar;
        }
    }
    return retVal; 
}

 /**
 * @brief Performs  transpose(mat)
 * this function will malloc for the user a matrix*
 * @return a matrix*
 * @param matA
 */
matrix* mat_transpose(const matrix* mat)
{
    matrix *retVal = matrix_create(mat->col, mat->row);
    for (size_t i = 0; i < mat->row; i++)
    {
        for (size_t j = 0; j < mat->col; j++)
        {
            MAT(retVal,j,i) = MAT(mat,i,j);
        }
    }
    return retVal;
}