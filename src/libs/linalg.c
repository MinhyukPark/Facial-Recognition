/**
 * @file linalg.c
 * @authon Minhyuk Park
 * @date 7 Nov 2017
 * @brief File containing common linear algebra functions.
 */
 
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
        printf("%f ", vec->data[i]);
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

 /**
 * @brief Performs  vecA = vecA+vecB
 * this function will realloc for the user vectorA
 * and destroys vecB
 * @return void
 * @param vecA
 * @param vecB
 */
void vec_append(vector** vecA, vector* vecB)
{
    vector *buffer = vector_create(vecB->size);
    memcpy(buffer, vecB, sizeof(double)*(vecB->size) + (2 * sizeof(size_t)));
    size_t newSize = (*vecA)->size + buffer->size;
    //vector* retVal = vector_create(newSize);
    void *dest = *vecA;
    void* arrv = NULL;
    arrv = realloc(dest, sizeof(double)*(newSize) + (2 * sizeof(size_t)));
    *vecA = arrv;
    //memcpy(vecA->data, vecA->data, newSize *sizeof(double) + (2 * sizeof(size_t)));    
    memcpy((*vecA)->data + (*vecA)->size, buffer->data, buffer->size *sizeof(double));
    (*vecA)->size = newSize;
    free(buffer);
    if(*vecA==vecB)
    {
        return;
    }
    free(vecB);
}

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
void eigen(int n, double a[], int it_max, double v[], double d[], int* it_num, int* rot_num) {
    mat_identity(n, v); // create the identity matrix using what the caller allocated for us
    diag_vector(n, a, d); // get the diagonal values of a and store it in caller allocated vector d

    double* bw = (double*) malloc(n * sizeof(double));
    double* zw = (double*) malloc(n * sizeof(double));

    for(int i = 0; i < n; i ++) {
        bw[i] = d[i];
        zw[i] = 0.0;
    }
    *it_num = 0;
    *rot_num = 0;

    double thresh = 0.0;
    double gapq = 0.0;
    while(*it_num < it_max) {
        *it_num += 1;
        thresh = 0.0;
        // set up the convergence threshold
        // based on the size of strict upper triangle
        for(int i = 0; i < n; i ++) {
            for(int j = 0; j < i; j ++) {
                thresh += (a[j + i * n] * a[j + i * n]);
            }
        }
        // PASS 1
        thresh = sqrt(thresh) / (double)(4 * n);
        if(thresh == 0.0) {
            break;
        }
        // PASS 2
        for(int p = 0; p < n; p ++) {
            for(int q = p + 1; q < n; q ++) {
                gapq = 10.0 * fabs(a[p + q * n]);
                double termp = gapq + fabs(d[p]);
                double termq = gapq + fabs(d[q]);
                if(4 < *it_num && termp == fabs(d[p]) && termq == fabs(d[q])) {
                    a[p + q * n] = 0.0;
                // apply rotation otherwise
                // PASS 3
                } else if(thresh <= fabs(a[p + q * n])) {
                    double h = d[q] - d[p];
                    double term = fabs(h) + gapq;
                    double t = 0.0;
                    if(term == fabs(h)) {
                        t = a[p + q * n] / h;
                    } else {
                        double theta = 0.5 * h / a[p + q * n];
                        t = 1.0 / (fabs(theta) + sqrt(1.0 + theta * theta));
                        if(theta < 0.0) {
                            t = -t;
                        }
                    }
                    // PASS 4
                    double c = 1.0 / sqrt(1.0 + t * t);
                    double s = t * c;
                    double tau = s / (1.0 + c);
                    h = t * a[p + q * n];

                    zw[p] -= h;
                    zw[q] += h;
                    d[p] -= h;
                    d[q] += h;
                    a[p + q * n] = 0.0;
                    // PASS 5
                    // rotate
                    double g = 0.0;
                    for(int j = 0; j < p; j ++) {
                        g = a[j + p * n];
                        h = a[j + q * n];
                        a[j + p * n] = g - s * (h + g * tau);
                        a[j + q * n] = h + s * (g - h * tau);
                    }
                    for(int j = p + 1; j < q; j ++) {
                        g = a[p + j * n];
                        h = a[j + q * n];
                        a[p + j * n] = g - s * (h + g * tau);
                        a[j + q * n] = h + s * (g - h * tau);
                    }
                    for(int j = q + 1; j < n; j ++) {
                        g = a[p + j * n];
                        h = a[q + j * n];
                        a[p + j * n] = g - s * (h + g * tau);
                        a[q + j * n] = h + s * (g - h * tau);
                    }
                    // PASS 6
                    // store to eigenvector matrix v
                    for(int j = 0; j < n; j ++) {
                        g = v[j + p * n];
                        h = v[j + q * n];
                        v[j + p * n] = g - s * (h + g * tau);
                        v[j + q * n] = h + s * (g - h * tau);
                    }
                    *rot_num += 1;
                }
            }
        }
        for(int i = 0; i < n; i ++) {
            bw[i] += zw[i];
            d[i] = bw[i];
            zw[i] = 0.0;
        }
    }
    // PASS 7
    // restore upper triangle
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < i; j ++) {
            a[j + i * n] = a [i + j * n];
        }
    }
    for(int k = 0; k < n - 1; k ++) {
        int m = k;
        for(int l = k + 1; l < n; l ++) {
            if(d[l] < d[m]) {
                m = l;
            }
        }
        if(m != k) {
            double t = d[m];
            d[m] = d[k];
            d[k] = t;
            for(int i = 0; i < n; i ++) {
                double w = v[i + m * n];
                v[i + m * n] = v[i + k * n];
                v[i + k * n] = w;
            }
        }
    }
    free(bw);
    free(zw);
    return;
}


/**
 * @brief returns an identity matrix of size n
 * @param n the dimension
 * @param a[] output identity matrix
 */
void mat_identity(int n, double a[]) {
    int k = 0;
    for (int j = 0; j < n; j ++ ) {
        for (int i = 0; i < n; i ++ ) {
            if ( i == j ) {
                a[k] = 1.0;
            } else {
                a[k] = 0.0;
            }
            k += 1;
        }
    }
    return;
}

/**
 * @brief gets the diagonal entries
 * @param n the dimension
 * @param a[] input the matrix, N by N
 * @param v[] output the diagonal entries, N
 */
void diag_vector(int n, double a[], double v[]) {
    for(int i = 0; i < n; i ++) {
        v[i] = a[i + i * n];
    }
    return;
}

/**
 * @brief computes the Frobenius norm in a right eigensystem
 * @param n the dimension of the matrix
 * @param k the number of eigen vectors
 * @param a[] input matrix of size n by n
 * @param x[] input vector of eigenvectors of size k
 * @param lamdba[] input vector of eigen values
 * @return double the frobenius norm of A * X - X * lambda
 */
double frobenius_norm(int n, int k, double a[], double x[], double lambda[]) {
    double* c = (double*) malloc(n * k * sizeof(double));
    for(int i = 0; i < k; i ++) {
        for(int j = 0; j < n; j ++) {
            c[j + i * n] = 0.0;
            for(int l = 0; l < n; l ++) {
                c[j + i * n] = c[j + i * n] + a[j + l * n] * x[l + i * n];
            }
        }
    }
    for(int i = 0; i < k; i ++) {
        for(int j = 0; j < n; j ++) {
            c[j + i * n] = c[j + i * n] - lambda[i] * x[j + i * n];
        }
    }
    // n k c
    // m n a
    double retval = 0.0;
    for(int i = 0; i < k; i ++) {
        for(int j = 0; j < n; j ++) {
            retval += pow(c[j + i * n], 2);
        }
    }
    retval = sqrt(retval);
    free(c);
    return retval;
}
