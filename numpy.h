#ifndef NUMPY_H
#define NUMPY_H

#include <stdio.h>
#include <stdlib.h>
#include "numpy.h"
typedef enum 
{
    INT,
    FLOAT
} DType;

typedef struct array
{
    void **lines;
    int *shape; 
    DType dtype;
} Array;


Array* array(void *data, int shape[], DType dtype);
void print_array(Array *arr);
void free_array(Array *arr);

#endif