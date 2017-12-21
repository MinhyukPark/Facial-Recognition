/**
 * @file facerec.c
 * @authon Minhyuk Park
 * @date 7 Nov 2017
 * @brief File containing the main function
 */

#include <assert.h>
#include "linalg.h" // unnecessary because tiff_util.h includes linalg.h
#include "tiff_util.h"


int train_dataset(const char* data_path) {

}

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

    
    matrix* normalized_image_col_matrix = image_col_matrix;

    for(int r = 0; r < normalized_image_col_matrix->row; r ++) {
        for(int c = 0; c < normalized_image_col_matrix->col; c ++) {
            MAT(normalized_image_col_matrix, r, c) -= VEC(average_image, r);
        }
    } 

    matrix* covariance_mat = covmat(normalized_image_col_matrix);
    double eigen_vectors[256 * 256];
    double eigen_values[256];
    int* it_num = NULL;
    int* rot_num = NULL;
    eigen(256, normalized_image_col_matrix->data, 100, eigen_vectors, eigen_values, it_num, rot_num);

    matrix* projection_matrix = matrix_create(256, 5);
 
    for(size_t i = 0; i < projection_matrix->col; i ++) {
        for(size_t j = 0; j < projection_matrix->row; j ++) {
            MAT(projection_matrix, i, j) = eigen_vectors[i * 256 + j];
        }
    }

    vector* good_face_one = vec_to_tiff("./dataset/jaffe/KA.NE2.27.tiff");
    vector* good_face_two = vec_to_tiff("./dataset/jaffe/MK.FE1.131.tiff");
    vector* bad_image_one = vec_to_tif("./dataset/jaffe/bad_image_one.tiff");
    vector* bad_image_two = vec_to_tif("./dataset/jaffe/bad_image_two.tiff");

    

    
    free(image_col_matrix);
    free(average_image);
    free(image_vector);
    pclose(out_pipe);

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