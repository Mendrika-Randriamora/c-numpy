#ifndef NUMPY_H
#define NUMPY_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "numpy.h"
#include <stdbool.h>
#include <string.h>

#define MAX_LENGHT_NAME 10

typedef struct __matrix__ {
    char name[MAX_LENGHT_NAME];
    unsigned int shape[3];
    float *data;
} Matrix;


Matrix *new_matrix(char[], unsigned int[3], float*, size_t);
void shape(Matrix *);
void view(Matrix *);

#endif