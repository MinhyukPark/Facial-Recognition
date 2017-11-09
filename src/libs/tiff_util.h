/**
 * @file tiff_util.h
 * @authon Minhyuk Park
 * @date 9 Nov 2017
 * @brief File containing common libtiff wrapper functions
 */
#pragma once

#include <stdlib.h>
#include <tiffio.h>
#include "linalg.h"

/**
 * @brief Converts tiff to vector
 * this function will take a TIFF file and
 * return a vector with every element corresponding to pixel
 * @return a vector*
 * @param TIFF* tiff image
 */
vector* tiff_to_vec(TIFF* image);

/**
 * @brief Converts vector to tiff
 * this function will take a vector and
 * return a TIFF* with every element corresponding to pixel
 * @return a TIFF*
 * @param char* the output filename
 * @param vector* vector representing the image
 */
TIFF* vec_to_tiff(char* filename, vector* vec);