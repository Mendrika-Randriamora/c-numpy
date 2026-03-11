#ifndef NUMPY_H
#define NUMPY_H

#include <stdio.h>
#include <stdlib.h>
#include "numpy.h"


typedef struct array
{
    int **lines;
    int *shape; 
} Array;


Array* array(int data[], int shape[]);
void print_array(Array *arr);
void free_array(Array *arr);

#endif