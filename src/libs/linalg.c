/**
 * @file linalg.c
 * @authon Minhyuk Park
 * @date 7 Nov 2017
 * @brief File containing common linear algebra functions.
 */
 
#include "linalg.h"
#include "tiff_util.h"

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


matrix* vec_to_mat(vector* vec, int orientation) {
    if(orientation == 1) {
        vec->padding = vec->size;
        vec->size = 1;
    } else {
        vec->padding = 1;
    }
    return (matrix*)vec;
}


void matrix_reshape(matrix* mat, size_t row, size_t col) {
    mat->row = row;
    mat->col = col;
}


double dot_product(const double* x, const double* y, int length)
{
    double retVal = 0.0;
    for(int i =0;i<length; i++)
    {
        retVal+=(x[i] *y[i]);
    }
    return retVal;
}


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


void mat_print(const matrix* mat) {
    for(size_t i = 0; i < mat->row; i ++) {
        for(size_t j = 0; j < mat->col; j ++) {
            if(j==mat->col-1)
            {
                printf("%f ", MAT(mat, i, j));                
            }
            else
            {
                printf("%f, ", MAT(mat, i, j));
            }
        }
        printf("\n");
    }
}


void vec_print(const vector* vec) {
    for(size_t i = 0; i < vec->size; i ++) {
        // printf("%f, ", VEC(vec, i));
        printf("%f ", vec->data[i]);
    }
    printf("\n");
}


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


void vec_append(vector** vec_a, vector* vec_b)
{
    void* saved_vec_a = *vec_a;
    vector* buffer = vector_create(vec_b->size);
    memcpy(buffer, vec_b, sizeof(double) * vec_b->size + (2 * sizeof(size_t)));
    size_t newSize = (*vec_a)->size + buffer->size;
    void* dest = *vec_a;
    void* arrv = NULL;
    arrv = realloc(dest, sizeof(double) * newSize + (2 * sizeof(size_t)));
    *vec_a = arrv;    
    memcpy((*vec_a)->data + (*vec_a)->size, buffer->data, buffer->size *sizeof(double));
    (*vec_a)->size = newSize;
    free(buffer);
    if(saved_vec_a != vec_b)
    {
        free(vec_b);
    }
}


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


void diag_vector(int n, double a[], double v[]) {
    for(int i = 0; i < n; i ++) {
        v[i] = a[i + i * n];
    }
    return;
}


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

matrix* covmat(matrix* mat) {
    size_t n = mat->row;
    matrix* mat_T = mat_transpose(mat);
    matrix* x_T_x = matmat_multiply(mat_T, mat);
    matrix* retmat = matscalar_divide(x_T_x, n);
    free(x_T_x);
    free(mat_T);
    return retmat;
}

matrix * compute_average(vector* images, int num_images)
{
    size_t number_of_tiffs = images->size;
    matrix *tiff_matrix = vec_to_mat(images, 1);
    matrix_reshape(tiff_matrix, (size_t)number_of_tiffs/num_images, (size_t)num_images); 
    matrix *transposed_tiff_matrix = mat_transpose(tiff_matrix);
    matrix* one_matrix = matrix_create(1,transposed_tiff_matrix->row);
    for(int i =0; i <num_images; i++)
    {
        MAT(one_matrix, 0,i) = 1;
    }
    matrix *multiplyMat = matmat_multiply(one_matrix, transposed_tiff_matrix);
    free(one_matrix);
    one_matrix = matrix_create(transposed_tiff_matrix->row, 1);
    for(size_t i =0; i < transposed_tiff_matrix->row; i++)
    {
        MAT(one_matrix, i, 0) = 1;
    }
    matrix *multiplyMat2 = matmat_multiply(one_matrix, multiplyMat);
    free(multiplyMat);
    matrix *multiplyMat3 = mat_transpose(multiplyMat2);
    free(multiplyMat2);    
    matrix *multiplyMat4 = matscalar_divide(multiplyMat3, num_images);
    matrix * subtractMat = matmat_subtraction(tiff_matrix, multiplyMat4);
    free(multiplyMat3);    
    free(one_matrix);
    free(transposed_tiff_matrix);
    free(multiplyMat4);
    return subtractMat;
}
