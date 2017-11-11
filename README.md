# Facial-Recognition
[![MIT license](https://img.shields.io/badge/License-MIT-blue.svg)](https://lbesson.mit-license.org/)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](https://github.com/dwyl/esta/issues)
![](https://img.shields.io/badge/maintained-yes-green.svg?style=flat)

:hourglass: *Work in Progress*

built with :heartpulse:

:lock: Signed using GPG

Facial Detection using Eigenfaces

## Motivation

Trying to apply what I learned in class about Principal Component Analysis and 
Singular Value Decomposition and create a C-library for a set of functions that
will determine whether a given image contains a humanly-recognizable face or not,
and if recognized if it is a face that is in the dataset.

## Dependencies

- [libtiff](http://www.libtiff.org/): TIFF Library and Utilities
  - [source code](external_libraries/libtiff) is distributed with this repo
  
## Installation
### libtiff

Once inside the [directory](external_libraries/libtiff), navigate to the version
of your choice and then run the following commands.
```
./configure --prefix=/usr --disable-static && make

sudo make install

make clean
make distclean
```
make sure to clean up the .tar file it creates or any other files
not cleaned up by the set of make clean commands to prevent
false commits/pull requests to master.

## How to Run

make sure all dependencies are satisfied before building

`make`
to build for release

`make debug`
to build for debugging

## Special Thanks to
 - TJ Egbejimba


## TODOs

### Design Decisions

When to malloc, realloc, free?

Does jacobi approximation provide enough accuracy?

Catastrophic cancellation when normalizing?

### Linear Algebra functions

~matmat_add()~

~matmat_subtract()~

~matscalar_multiply()~

~matscalar_divide()~

~mat_transpose()~

~vec_append()~

mat_average()

### Libtiff

~tiff_to_vec()~

~vec_to_tiff()~

get_all_tiff_files()

### Optimizations (for the UIUC linux cluster)

prefetching for large linear algebra operations

optimizing cache behavior
