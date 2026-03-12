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

typedef struct 
{
    int Int;
    float Float;
} DataT;


typedef struct array
{
    void **lines;
    int *shape; 
    DType dtype;
} Array;


Array* array(void *data, int shape[], DType dtype);
Array* ones(int shape[], DType type);
Array* zeros(int shape[], DType type);
Array* zeros_like(Array *arr);

void print_array(Array *arr);
void free_array(Array *arr);

#endif