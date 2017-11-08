#include "linalg.h"
#include <stdio.h>

int main() {
    double** mat = vecmat_multiply(NULL, NULL);
    printf("%p", mat);
    return 0;
}