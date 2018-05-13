/*
 * @file facerec.c
 * @authon Minhyuk Park
 * @date 7 Nov 2017
 * @brief File containing the main function
 */

#include <assert.h>
#include "linalg.h" // unnecessary because tiff_util.h includes linalg.h
#include "tiff_util.h"

int main() {
    // vector* vec = vector_create(5);
    // matrix* mat = matrix_create(5, 5);
    // for(size_t i = 0; i < vec->size; i ++) {
    //     vec->data[i] = i;
    // }

    // for(size_t i = 0; i < mat->row * mat->col ; i ++) {
    //     mat->data[i] = i;
    // }

    // vector* vecmat_result = matvec_multiply(mat, vec);
    // vec_print(vecmat_result);

    // vector* matvec_result = matvec_multiply(mat,vec);
    // vec_print(matvec_result);

    // matrix* converted_vecmat = vec_to_mat(vecmat_result, 0);
    // mat_print(converted_vecmat);

    // matrix* converted_matvec = vec_to_mat(matvec_result, 1);
    // mat_print(converted_matvec);

    // matrix * matmat_result = matmat_multiply(mat,mat);
    // mat_print(matmat_result);    
    
    // matrix *matsub_result = matmat_subtraction(mat,mat);
    // mat_print(matsub_result);      

    // matrix *matadd_result = matmat_addition(mat,mat);
    // mat_print(matadd_result);   

    // matrix *matscaleMult_result = matscalar_multiply(mat,5);
    // mat_print(matscaleMult_result);

    // matrix *matscaleDiv_result = matscalar_divide(mat,5);
    // mat_print(matscaleDiv_result);
  
    // matrix *mattranspose_result = mat_transpose(mat);
    // mat_print(mattranspose_result);

    // vector* image_vec = tiff_to_vec("./dataset/jaffe/KA.AN1.39.tiff");
    // TIFF* out = vec_to_tiff("./dataset/jaffe/test.tiff", image_vec);
    // printf("sizeof vec %zu", image_vec->size);
    // TIFFClose(out);
    // free(image_vec);
    // remove("./dataset/jaffe/test.tiff");
    // printf("\n\n");
    // vec_print(vec);    
    // vec_append(&vec,vec);
    // vec_print(vec);

    // double a[25] = {
    //     4,  4,    2,   3,     -2, 
    //     4,  1,  -2,   -2,   2, 
    //     2, -2,  11, 2,  -4, 
    //     3,  -2, 2,   10, -6,
    //     -2, 2, -4, -6, -3 };
    // double d[5];
    // int it_max = 100;
    // int it_num;
    // int n = 5;
    // int rot_num;
    // double v[25];
    // eigen( n, a, it_max, v, d, &it_num, &rot_num );

    // printf("num iter = %d\n", it_num);
    // printf("num rot = %d\n", rot_num);
    // printf("eigenvalues: ");
    // for(int i = 0; i < 5; i ++) {
    //     printf("%f, ", d[i]);    
    // }
    // printf("\n");
    
    // double error_frobenius = frobenius_norm(n, n, a, v, d);
    // printf("error of A * V - D * V = %g\n",  error_frobenius);
    // vector* vec = vector_create(12);

    //  double b[12] = {
    //      0, 5, 10,
    //      0, 10, 20,
    //      0, 15, 30,
    //      0, 20, 40 };

    // for(size_t i = 0; i < vec->size; i ++) {
    //     vec->data[i] = b[i];
    // }
    // matrix* images = vec_to_mat(vec, 0);
    // matrix_reshape(images, 4, 3);
    // vector* compute_average_test = compute_average(images, 3);
    // vec_print(compute_average_test);

    // free(compute_average_test);
    // free(vec);
    

    // matrix* variance_covariance_mat = covmat(mat);
    // mat_print(variance_covariance_mat);

    // free(mat);
    // free(variance_covariance_mat);

    
    int num_files;
    FILE* out_pipe = get_all_tiff("./dataset/jaffe/", &num_files);
    vector* image_vector = tiff_stream_to_vec(out_pipe);
    matrix* image_matrix = vec_to_mat(image_vector, 0);
    matrix_reshape(image_matrix, num_files, image_matrix->row / num_files);
    printf("row: %zu    col: %zu\n", image_matrix->row, image_matrix->col);
    matrix* image_col_matrix = mat_transpose(image_matrix);
    vector* average_image = compute_average(image_col_matrix, num_files);

    printf("size: %zu\n", average_image->size);
    TIFF* avg_tiff = vec_to_tiff("average_face.tiff", average_image, 256, 256);

    TIFFClose(avg_tiff);
    free(image_col_matrix);
    free(image_matrix); 
    pclose(out_pipe);

    

    FILE* second_out_pipe = get_all_tiff("./dataset/jaffe/", &num_files);
    vector* total_image_vector = tiff_stream_to_vec(second_out_pipe);
    matrix* total_image_matrix = vec_to_mat(total_image_vector, 0);
    matrix_reshape(total_image_matrix, num_files, total_image_matrix->row / num_files);
    matrix* total_image_col_matrix = mat_transpose(total_image_matrix);
    
    size_t total_image_col_matrix_row = total_image_col_matrix->row;
    size_t total_image_col_matrix_col = total_image_col_matrix->col;
    free(total_image_matrix);
    pclose(second_out_pipe);   
    
    
    printf("creating A\n"); 
    matrix* average_col_matrix = matrix_create(total_image_col_matrix_row, total_image_col_matrix_col);
    for(size_t i = 0;  i < average_col_matrix->row; i ++) {
        for(size_t j = 0; j < average_col_matrix->col; j ++) {
            MAT(average_col_matrix, i, j) = VEC(average_image, i);
        }
    } 
    free(average_image);

    matrix* orth_mat = matmat_subtraction(total_image_col_matrix, average_col_matrix);
    free(total_image_col_matrix);
    free(average_col_matrix);

    printf("creating ATA\n");
    matrix* covar_matrix = covmat(orth_mat);
    int covar_matrix_row = (int)covar_matrix->row;
    // int covar_matrix_col = (int)covar_matrix->col;
    vector* covar_vec = mat_to_vec(covar_matrix);

     

    /*
    double a[25] = {
        4,  4,    2,   3,     -2, 
        4,  1,  -2,   -2,   2, 
        2, -2,  11, 2,  -4, 
        3,  -2, 2,   10, -6,
        -2, 2, -4, -6, -3 };
    double d[5];
    double v[25];
    */
    int it_max = 100;
    int it_num;
    int n = covar_matrix_row; 
    int rot_num;
    double* d = malloc(sizeof(double) * n);
    double* v = malloc(sizeof(double) * n * n); 
    eigen( n, covar_vec->data, it_max, v, d, &it_num, &rot_num );

    printf("num iter = %d\n", it_num);
    printf("num rot = %d\n", rot_num);
    printf("eigenvalues: ");
    for(int i = 0; i < 5; i ++) {
        printf("%f, ", d[i]);    
    }
    printf("\n");
    
    double error_frobenius = frobenius_norm(n, n, covar_vec->data, v, d);
    printf("error of A * V - D * V = %g\n",  error_frobenius);
    
    int num_eigen_values = 4;
    matrix* eigen_space = matrix_create(n, num_eigen_values);
    for(size_t i = 0; i < eigen_space->row; i ++) {
        for(size_t j = 0; j < eigen_space->col; j ++) {
            MAT(eigen_space, i, j) = v[(j* n) + i];
        }
    } 

    /*
    matrix* orth_mat_transpose = mat_transpose(orth_mat);
    free(orth_mat);
 
    for(int i = 0; i < num_eigen_values; i ++) {
        vector* before_scale = vector_create(n);
        for(int j = 0; j < n; j ++) {
            VEC(before_scale, j) = MAT(eigen_space, j, i);
        }
        vector* after_scale = matvec_multiply(orth_mat_transpose, before_scale);
        for(int j = 0; j < n; j ++) {
            MAT(eigen_space, j, i) = VEC(after_scale, j);
        }
        free(before_scale);
        free(after_scale);
    }
    */

    free(d);
    free(v);
    free(covar_vec);

    matrix* eigen_space_transpose = mat_transpose(eigen_space);
    matrix* weights = matmat_multiply(eigen_space, eigen_space_transpose);
    
    free(eigen_space);
    free(eigen_space_transpose);
    
    double error_positive_1 = 0.0;
    double error_positive_2 = 0.0;
    double error_negative_1 = 0.0;
    double error_negative_2 = 0.0;

    vector* face_1 = tiff_to_vec("./dataset/jaffe/KA.AN1.39.tiff");
    matrix* face_1_mat = vec_to_mat(face_1, 0);
    
    vector* face_2 = tiff_to_vec("./dataset/jaffe/KA.AN2.40.tiff");
    matrix* face_2_mat = vec_to_mat(face_2, 0);

    vector* not_face_1 = tiff_to_vec("./dataset/fake_jaffe/keith_haring_heart.tiff");
    matrix* not_face_1_mat = vec_to_mat(not_face_1, 0);

    vector* not_face_2 = tiff_to_vec("./dataset/fake_jaffe/kaya_screenshot.tiff");
    matrix* not_face_2_mat = vec_to_mat(not_face_2, 0);

    for(int i = 0; i < 4; i ++) {
        for(size_t j = 0; j < weights->row; j ++) {
            for(size_t k = 0; k < weights->col; k ++) {
                error_positive_1 += pow(MAT(weights, j, k) - MAT(face_1_mat, j, k), 2);
                error_positive_2 += pow(MAT(weights, j, k) - MAT(face_2_mat, j, k), 2);
                error_negative_1 += pow(MAT(weights, j, k) - MAT(not_face_1_mat, j, k), 2);
                error_negative_2 += pow(MAT(weights, j, k) - MAT(not_face_2_mat, j, k), 2);
            }
        }
    }

    printf("distance of positive 1 is %g\n", sqrt(error_positive_1));
    printf("distance of positive 2 is %g\n", sqrt(error_positive_2));
    printf("distance of negative 1 is %g\n", sqrt(error_negative_1));
    printf("distance of negative 2 is %g\n", sqrt(error_negative_2));

    free(face_1_mat);
    free(face_2_mat);
    free(not_face_1_mat);
    free(not_face_2_mat);
    free(weights);
    
    
    

    // free(converted_vecmat);
    // free(converted_matvec);
    // free(matmat_result);
    // free(matsub_result);
    // free(matadd_result);    
    // free(matscaleMult_result);
    // free(matscaleDiv_result);
    // free(mattranspose_result);
    return 0;
}
