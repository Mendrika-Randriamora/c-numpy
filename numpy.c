#include "numpy.h"

Array* array(int data[], int shape[])
{
    Array *arr = malloc(sizeof(Array));

    arr->shape = malloc(2 * sizeof(int));
    for (int k = 0; k < 2; k++)
    {
        arr->shape[k] = shape[k];
    }
    
    arr->lines = malloc(shape[0] * sizeof(int *));

    int index = 0;

    for (int i = 0; i < shape[0]; i++)
    {
        int *ln = malloc(shape[1] * sizeof(int));

        for (int j = 0; j < shape[1]; j++)
        {
            ln[j] = data[j + index];
        }

        arr->lines[i] = ln;
        index += shape[1];        

    }
    
    // printf("(%d, %d)\n", shape[0], shape[1]);
    return arr;
}

void print_array(Array *arr)
{
    for (int i = 0; i < arr->shape[0]; i++)
    {
        for (int j = 0; j < arr->shape[1]; j++)
        {
            printf("%d ", arr->lines[i][j]);
        }

        printf("\n");
        
    }
}

void free_array(Array *arr) 
{
    for (int i = 0; i < arr->shape[0]; i++)
    {
        free(arr->lines[i]);
    }

    free(arr->shape);
    free(arr->lines);
    free(arr);
}