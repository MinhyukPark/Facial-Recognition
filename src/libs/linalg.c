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

vector* mat_to_vec(matrix* mat) {
    assert(mat->row = 1);
    mat->row = mat->col;
    mat->col = 1;
    return (vector*)mat;
}


void matrix_reshape(matrix* mat, size_t row, size_t col) {
    mat->row = row;
    mat->col = col;
}


double dot_product(const double* left, const double* right, int length) {
    double retval = 0.0;
    for(int i = 0; i < length; i ++) {
        retval += (left[i] * right[i]);
    }
    return retval;
}


vector* vecscalar_multiply(const vector* vec, const double scalar) {
    vector* retval = vector_create(vec->size);
    for (size_t i = 0; i < retval->size; i ++) {
        VEC(retval, i) = VEC(vec, i) * scalar;
    }
    return retval; 
}

vector* vecscalar_divide(const vector* vec, const double scalar) {
    return vecscalar_multiply(vec, 1 / scalar);
}



 vector* vecmat_multiply(const vector* vec, const matrix* mat) {
    if(vec == NULL  || mat == NULL) {
        return NULL;
    }
    vector* retval = vector_create(vec->size);
    memset(retval->data, 0, sizeof(double) * vec->size);
    for(size_t j = 0; j < mat->col; j ++) {
        for(size_t i = 0; i < mat->row; i ++) {
            VEC(retval, j) += (VEC(vec, i) * MAT(mat, i, j));
        }
    }
    return retval;
}


vector* matvec_multiply(const matrix* mat, const vector* vec) {
    if(vec == NULL  || mat == NULL) {
        return NULL;
    }
    vector* retval = vector_create(vec->size);
    for(size_t i = 0; i < retval->size; i++) { 
        VEC(retval,i) = dot_product(((double*)(mat->data) + (mat->col * i)), (double*)vec->data, vec->size);
    }
    return retval;
}


void mat_print(const matrix* mat) {
    for(size_t i = 0; i < mat->row; i ++) {
        for(size_t j = 0; j < mat->col; j ++) {
            if(j == mat->col - 1) {
                printf("%f ", MAT(mat, i, j));                
            } else {
                printf("%f, ", MAT(mat, i, j));
            }
        }
        printf("\n");
    }
}


void vec_print(const vector* vec) {
    for(size_t i = 0; i < vec->size; i ++) {
        printf("%f ", vec->data[i]);
    }
    printf("\n");
}


matrix* matmat_multiply(const matrix* left, const matrix* right) {
    matrix* retval = matrix_create(left->row, right->col);
    for(size_t i = 0; i < left->row; i ++) {
        for(size_t j = 0; j < right->col; j ++) {
            MAT(retval,i,j) = 0;
            for(size_t k = 0; k < left->col; k ++) {
                MAT(retval, i, j) += MAT(left, i, k) * MAT(right, k, j);
            }
        }
    }   
    return retval;
}


matrix* matmat_addition(const matrix* left, const matrix* right) {
    matrix* retval = matrix_create(left->row, right->col);
    for (size_t i = 0; i < left->row; i ++) {
       for (size_t j = 0; j < right->col; j ++) {
            MAT(retval, i, j) = MAT(left, i, j) + MAT(right, i, j);
        }
    }
    return retval;
}


matrix* matmat_subtraction(const matrix* left, const matrix* right) {
    matrix* retval = matrix_create(left->row, right->col);
    for (size_t i = 0; i < left->row; i ++) {
        for (size_t j = 0; j < right->col; j ++) {
            MAT(retval, i, j) = MAT(left, i, j) - MAT(right, i, j);
        }
    }
    return retval;
}


matrix* matscalar_multiply(const matrix* mat, const double scalar) {
    matrix* retval = matrix_create(mat->row, mat->col);
    for (size_t i = 0; i < mat->row; i++) {
        for (size_t j = 0; j < mat->col; j++) {
            MAT(retval,i,j) = MAT(mat,i,j) * scalar;
        }
    }
    return retval;
}


matrix* matscalar_divide(const matrix* mat, const double scalar) {
    return matscalar_multiply(mat, 1/scalar);
}


matrix* mat_transpose(const matrix* mat) {
    matrix* retval = matrix_create(mat->col, mat->row);
    for (size_t i = 0; i < mat->row; i ++) {
        for (size_t j = 0; j < mat->col; j ++) {
            MAT(retval, j, i) = MAT(mat, i, j);
        }
    }
    return retval;
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

vector* compute_average(matrix* images, int num_images) {
    /*
    matrix* ones_row = matrix_create(1, num_images);
    for(int i =0; i <num_images; i++) {
        MAT(ones_row, 0,i) = 1;
    }
    matrix* row_images = mat_transpose(images);
    matrix* row_sum = matmat_multiply(ones_row, row_images);
    vector* vector_row_sum = mat_to_vec(row_sum);
    vector* img_avg = vecscalar_divide(vector_row_sum, num_images);
    free(vector_row_sum);
    free(row_images);
    free(ones_row);
    */
    vector* img_avg = vector_create(images->row);

    for(size_t i = 0; i < img_avg->size; i ++) {
        uint32 avg_pixel = 0;

        uint32 r = 0;
        uint32 g = 0;
        uint32 b = 0;
        uint32 a = 0;
        for(int j = 0; j < num_images; j ++) {
            uint32 current_pixel = MAT(images, i, j);

            r += ((current_pixel & 0xff) * (current_pixel & 0xff));
            g += (((current_pixel >> 8) & 0xff) * ((current_pixel >> 8) & 0xff));
            b += (((current_pixel >> 16) & 0xff) * ((current_pixel >> 16) & 0xff));
            a += (((current_pixel >> 24) & 0xff) * ((current_pixel >> 24) & 0xff));
        }

        r /= num_images;
        g /= num_images;
        b /= num_images;
        a /= num_images;

        r = sqrt(r);
        g = sqrt(g);
        b = sqrt(b);
        a = sqrt(a);
        /*
        for(int j = 0; j < num_images; j ++) {
            uint32 current_pixel = MAT(images, i, j);

            r += ((current_pixel & 0xff));
            g += (((current_pixel >> 8) & 0xff));
            b += (((current_pixel >> 16) & 0xff));
            a += (((current_pixel >> 24) & 0xff));
        }

        r /= num_images;
        g /= num_images;
        b /= num_images;
        a /= num_images;
        */


        avg_pixel |= r;
        avg_pixel |= (g << 8);
        avg_pixel |= (b << 16);
        avg_pixel |= (a << 24);

        VEC(img_avg, i) = avg_pixel;
    }


    

    return img_avg;
}
