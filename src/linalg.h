/**
 * @file linalg.h
 * @authon Minhyuk Park
 * @date 7 Nov 2017
 * @brief File containing common linear algebra functions.
 */
#pragma once

#include <stdlib.h>

/**
 * @brief Performs vector * matrix
 * this function will malloc for the user a double**
 * @return a double** representing a matrix
 * @param vec
 * @param mat
 */
 double** vecmat_multiply(double* vec, double** mat);
 