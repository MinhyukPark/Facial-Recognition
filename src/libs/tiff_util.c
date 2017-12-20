/**
 * @file tiff_util.c
 * @authon Minhyuk Park
 * @date 9 Nov 2017
 * @brief File containing common libtiff wrapper functions
 */
 
#include "tiff_util.h"
#include <math.h>

vector* tiff_to_vec(char* filename) {
    TIFF* image = TIFFOpen(filename, "r");
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
    _TIFFfree(raster);

    retvec->padding = width;
    TIFFClose(image);
    return retvec;
}


TIFF* vec_to_tiff(char* filename, vector* vec, size_t width, size_t height) {
    TIFF* rettiff = TIFFOpen(filename, "w");

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

    for (uint32 i = 0; i < height; i++) {
        memcpy(buf, &image_char[(height - i - 1) * linebytes], linebytes);
        if (TIFFWriteScanline(rettiff, buf, i, 0) < 0) {
            break;
        }
    }
    _TIFFfree(buf);
    free(image_char);
    return rettiff;
}


FILE* get_all_tiff(char* path, int* num_files) {
    char* command = malloc(strlen(path) + 100);
    sprintf(command, "%s%s%s", "find ", path, "*.tiff -type f -exec ls {} \\;");
     
    
    printf("%s\n", command);
    FILE* retval = popen(command, "r");

    sprintf(command, "%s%s%s", "find ", path, "*.tiff -type f -exec ls {} \\; | wc -l");
    
    printf("%s\n", command);
    FILE* num_files_fp = popen(command, "r");
    if(fgets(command, sizeof(command), num_files_fp) != NULL) {
        *num_files = atoi(command);
    }
    pclose(num_files_fp);
    free(command);
    return retval;
}


vector* tiff_stream_to_vec(FILE* stream) {
    char* image_filename;
    char buffer[4096];

    vector* cumulative_image = NULL;
    while(fgets(buffer, sizeof(buffer), stream) != NULL) {
        image_filename = malloc(100);
        strcpy(image_filename, buffer);
        image_filename[strlen(image_filename) - 1] = '\0';
        if(cumulative_image == NULL) {
            cumulative_image = tiff_to_vec(image_filename);
        } else {
            vec_append(&cumulative_image, tiff_to_vec(image_filename));
        }
        free(image_filename);
    }
    return cumulative_image;
}