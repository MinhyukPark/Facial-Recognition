/**
 * @file tiff_util.h
 * @authon Minhyuk Park
 * @date 9 Nov 2017
 * @brief File containing common libtiff wrapper functions
 */
#pragma once

#include <stdlib.h>
#include <tiffio.h>
#include <unistd.h>
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
 * @param width size_t width of the image
 * @param height size_t height of the image
 */
TIFF* vec_to_tiff(char* filename, vector* vec, size_t width, size_t height);

/**
 * @brief Recursively earches the path for all files of .tiff type
 * the search relies on being able to run the commands
 * find and ls
 * @return FILE* the stream containing all the files separated by
 * new line characters
 * @param path char* the path containing the files
 * @param num_files int* outputs the number of files read
 */
FILE* get_all_tiff(char* path, int* num_files);

/**
 * @brief Converts FILE* tiff stream into a vector
 * the images are appended row-wise
 * @return vector* newly malloced vector* containing all the images
 * from the stream
 * @param stream FILE* returned from get_all_tiff()
 */
vector* tiff_stream_to_vec(FILE* stream);