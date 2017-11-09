#include <stdio.h>
#include <assert.h>
#include "linalg.h"
#include "tiff_util.h"

int main() {
    vector* vec = vector_create(5);
    matrix* mat = matrix_create(5, 5);
    for(size_t i = 0; i < vec->size; i ++) {
        vec->data[i] = i;
    }

    for(size_t i = 0; i < mat->row * mat->col ; i ++) {
        mat->data[i] = i;
    }

    vector* vecmat_result = matvec_multiply(mat, vec);
    vec_print(vecmat_result);

    vector* matvec_result = matvec_multiply(mat,vec);
    vec_print(matvec_result);

    matrix* converted_vecmat = vec_to_mat(vecmat_result, 0);
    mat_print(converted_vecmat);

    matrix* converted_matvec = vec_to_mat(matvec_result, 1);
    mat_print(converted_matvec);

    matrix * matmat_result = matmat_multiply(mat,mat);
    mat_print(matmat_result);    
    
    matrix *matsub_result = matmat_subtraction(mat,mat);
    mat_print(matsub_result);      

    matrix *matadd_result = matmat_addition(mat,mat);
    mat_print(matadd_result);   

    matrix *matscaleMult_result = matscalar_multiply(mat,5);
    mat_print(matscaleMult_result);

    matrix *matscaleDiv_result = matscalar_divide(mat,5);
    mat_print(matscaleDiv_result);
  
    matrix *mattranspose_result = mat_transpose(mat);
    mat_print(mattranspose_result);

    TIFF* image = TIFFOpen("./dataset/jaffe/KA.AN1.39.tiff", "r");
    vector* image_vec = tiff_to_vec(image);
    TIFF* out = vec_to_tiff("./dataset/jaffe/test.tiff", image_vec);
    printf("sizeof vec %zu", image_vec->size);
    TIFFClose(image);
    TIFFClose(out);
    free(image_vec);
    remove("./dataset/jaffe/test.tiff");

    free(vec);
    free(mat);
    free(converted_vecmat);
    free(converted_matvec);
    free(matmat_result);
    free(matsub_result);
    free(matadd_result);    
    free(matscaleMult_result);
    free(matscaleDiv_result);
    free(mattranspose_result);
    return 0;
}