/**
 * @file tiff_process.h
 * @authon Minhyuk Park
 * @date 9 Nov 2017
 * @brief File containing common libtiff wrapper functions
 */
#pragma once

#include <stdlib.h>
#include <tiffio.h>

/**
 * @brief Converts tiff to vector
 * this function will read a tiff file from disk and 
 * return a vector with every element corresponding to pixel
 * @return a vector*
 * @param char* filename of the tiff image
 */
vector* tiff_to_vec(char* filename);

/**
 * @brief Converts vector to tiff
 * this function will take a vector and
 * return a TIFF* with every element corresponding to pixel
 * @return a TIFF*
 * @param vector* vector representing the image
 */
TIFF* tiff_to_vec(vector* vec);