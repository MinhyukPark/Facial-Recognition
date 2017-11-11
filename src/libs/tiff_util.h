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
 * this function will take a TIFF filename and
 * return a vector* with every element corresponding to pixel
 * @return vector* newly malloced representing the image
 * @param filename char* the input filename
 */
vector* tiff_to_vec(char* filename);

/**
 * @brief Converts vector to tiff
 * this function will take a vector and
 * return a TIFF* with every element corresponding to pixel
 * @return TIFF* opened tiff file stream with necessary data written to from the
 * vector
 * @param filename char* the output filename
 * @param vec vector* vector representing the image
 */
TIFF* vec_to_tiff(char* filename, vector* vec);