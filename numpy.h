#ifndef NUMPY_H
#define NUMPY_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "numpy.h"
#include <stdbool.h>

/**
 * This is a enum for function to masked array
 * We use it when we create a mask of matrix like a parameter to know the 
 * type of mask (condition of mask)
 */
typedef enum
{
    BT, // Better than
    LT, // Less than
    EQ // Equal
} CoType;

/**
 * Structure of matrix
 */
typedef struct array
{
    float **lines; // All values of our matrix line per line
    int *shape; // Header of matrix
} Array;

Array* array(float *data, size_t len, int shape[]);
Array* ones(int shape[]);
Array* zeros(int shape[]);
Array* zeros_like(Array *arr);
Array* eye(int shape[]);

void add_nbr(Array *arr, float b);
Array* sum(Array *arr1, Array *arr2);
Array* dot(Array *arr1, Array *arr2);

Array* T(Array *arr);
Array* mask(Array *arr, CoType tp, float value);

void print_array(Array *arr);
void free_array(Array *arr);

#endif
