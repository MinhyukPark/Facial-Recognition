/**
 * @file tiff_util.c
 * @authon Minhyuk Park
 * @date 9 Nov 2017
 * @brief File containing common libtiff wrapper functions
 */
 
#include "tiff_util.h"
#include <math.h>

/**
 * @brief Converts tiff to vector
 * this function will take a TIFF file and
 * return a vector with every element corresponding to pixel
 * @return a vector*
 * @param TIFF* tiff image
 */
vector* tiff_to_vec(TIFF* image) {
    uint32 width;
    uint32 height;
    TIFFGetField(image, TIFFTAG_IMAGEWIDTH, &width);
    TIFFGetField(image, TIFFTAG_IMAGELENGTH, &height);

    uint32 num_pixels = width * height;
    uint32 * raster=(uint32*) _TIFFmalloc(num_pixels * sizeof(uint32));
    vector* retvec = vector_create(num_pixels);

    TIFFReadRGBAImage(image, width, height, raster, 0);

    for(size_t i = 0; i < num_pixels; i ++) {
        VEC(retvec, i) = *(raster + i);
    }

    retvec->padding = width;
    return retvec;
}

/**
 * @brief Converts vector to tiff
 * this function will take a vector and
 * return a TIFF* with every element corresponding to pixel
 * @return a TIFF*
 * @param char* the output filename
 * @param vector* vector representing the image
 */
TIFF* vec_to_tiff(char* filename, vector* vec) {
    TIFF* rettiff = TIFFOpen(filename, "w");
    uint32 width = vec->padding;
    uint32 height = vec->size / vec->padding;

    char* image_char = malloc(vec->size * 4); // 4 since RGBA

    for(size_t i = 0; i < vec->size; i ++) {
        image_char[4 * i] = (char)TIFFGetR((uint32)VEC(vec, i));
        image_char[4 * i + 1] = (char)TIFFGetG((uint32)VEC(vec, i));
        image_char[4 * i + 2] = (char)TIFFGetB((uint32)VEC(vec, i));
        image_char[4 * i + 3] = (char)TIFFGetA((uint32)VEC(vec, i));
    }
    TIFFSetField (rettiff, TIFFTAG_IMAGEWIDTH, width);
    TIFFSetField(rettiff, TIFFTAG_IMAGELENGTH, height);
    TIFFSetField(rettiff, TIFFTAG_SAMPLESPERPIXEL, 4);
    TIFFSetField(rettiff, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(rettiff, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(rettiff, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(rettiff, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);

    tsize_t linebytes = 4 * width;
    unsigned char* buf = NULL;

    if (TIFFScanlineSize(rettiff) == linebytes) {
        buf =(unsigned char*)_TIFFmalloc(linebytes);
    } else {
        buf = (unsigned char*)_TIFFmalloc(TIFFScanlineSize(rettiff));
    }

    TIFFSetField(rettiff, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(rettiff, width * 4));

    for (uint32 i = 0; i < height; i++)
    {
        memcpy(buf, &image_char[(height - i - 1) * linebytes], linebytes);
        if (TIFFWriteScanline(rettiff, buf, i, 0) < 0) {
            break;
        }
    }
    return rettiff;
}