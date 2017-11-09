/**
 * @file tiff_process.c
 * @authon Minhyuk Park
 * @date 9 Nov 2017
 * @brief File containing common libtiff wrapper functions
 */
#include "tiff_process.h"

/**
 * @brief Converts tiff to vector
 * this function will take a TIFF file and
 * return a vector with every element corresponding to pixel
 * @return a vector*
 * @param TIFF* tiff image
 */
vector* tiff_to_vec(TIFF* image) {
}

/**
 * @brief Converts vector to tiff
 * this function will take a vector and
 * return a TIFF* with every element corresponding to pixel
 * @return a TIFF*
 * @param vector* vector representing the image
 */
TIFF* tiff_to_vec(vector* vec) {
}