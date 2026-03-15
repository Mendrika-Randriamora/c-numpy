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
    float **lines;
    int *shape;
} Array;


Array* array(float *data, int shape[]);
Array* ones(int shape[]);
Array* zeros(int shape[]);
Array* zeros_like(Array *arr);
Array* eye(int shape[]);

void add_nbr(Array *arr, float b);
Array* sum(Array *arr1, Array *arr2);
Array* dot(Array *arr1, Array *arr2);

Array* T(Array *arr);

void print_array(Array *arr);
void free_array(Array *arr);

#endif
