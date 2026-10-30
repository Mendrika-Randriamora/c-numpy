#include "numpy.h"
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

bool is_same_shape_matrix(Array *arr1, Array *arr2) {
    return arr1->shape[0] == arr2->shape[0] && arr1->shape[1] == arr2->shape[1];
}

/**
 * Function to build a matrix
 * 
 * @param data simple pointer array which contains all values
 * @param len lenght of data
 * @param shape shape of matrix (only 2 elements, otherwise it's not work -> I don't implement again the code for verification)
 * shape[0] : lines
 * shape[1] : columns
 * 
 * @return array The array 
 */
Array* array(float *data, size_t len, int shape[])
{
    /**
     * Simple verification if shape corresponds with the data
     */
    if(len != shape[0]*shape[1]) {
        fprintf(stderr, "Can't build this matrix %ld != %d\n", len, shape[0]*shape[1]);
        exit(1);
    }
    
    Array *arr = malloc(sizeof(Array));

    // Transfer shape into matrix shape attribut
    arr->shape = malloc(2 * sizeof(int));
    for (int k = 0; k < 2; k++)
    {
        arr->shape[k] = shape[k];
    }

    /**
     * Allocate memory for all lines
     * This allocate only lines but not the element on lines 
    */
    arr->lines = malloc(shape[0] * sizeof(float *));

    int index = 0;

    for (int i = 0; i < shape[0]; i++)
    {
        // Allocate memory for all values on one line
        void *ln = malloc(shape[1] * sizeof(float));

        for (int j = 0; j < shape[1]; j++)
        {
            // Insert values on current line
            ((float*)ln)[j] = ((float*)data)[j + index];
        }

        // Insert current line in our matrix
        arr->lines[i] = ln;
        index += shape[1];

    }

    return arr;
}

/**
 * Function to generate an array for the future function 
 * It's generate a simple 1d pointer array
 * 
 * @param shape to know the lenght or dim or array
 * @param dt the value that contains this array
 * 
 * @return array No comment
 */
void* gen(int shape[], float dt)
{
    int dim = shape[0] * shape[1];
    void *data = malloc(dim * sizeof(float));

    float *ptr = data;

    for (int i = 0; i < dim; i++)
    {
        ptr[i] = dt;
    }

    return data;

}

/**
 * To generate matrix wthis one in entire matrix
 */
Array* ones(int shape[])
{
    void * data = gen(shape, 1.0);

    return array(data, shape[0]*shape[1], shape);

}

/**
 * To generate matrix wthis zero in entire matrix
 */
Array* zeros(int shape[])
{
    void * data = gen(shape, 0.0);

    return array(data, shape[0]*shape[1], shape);

}

/**
 * To generate matrix wthis zero in entire matrix like a ...
 */
Array* zeros_like(Array *arr)
{
    return zeros(arr->shape);
}

/**
 * Function to generate a matrix indetity
 */
Array* eye(int shape[])
{
    if (shape[0] != shape[1]) {
        fprintf(stderr, "Eye matrix need a square matrix");
        exit(1);
    }

    Array* temp = zeros(shape);

    for (int i = 0; i < shape[0]; i++)
    {
        ((float *)temp->lines[i])[i] = 1.0;
    }

    return temp;
}

// ================= Arithmetic ======================= //
/*
 * Function to add a number on matrix
 */
void add_nbr(Array *arr, float a)
{
    for (int i = 0; i < arr->shape[0]; i++)
    {
        for (int j = 0; j < arr->shape[1]; j++)
        {
            ((float *)arr->lines[i])[j] += a;
        }

    }

}

/**
 * Function to calculate a sum of two same matrix
 * 
 * @param arr1 first matrix
 * @param arr2 second matrix
 * 
 * @return T sum of the matrix
 */
Array* sum(Array *arr1, Array *arr2)
{
    if (!is_same_shape_matrix(arr1, arr2)) {
        fprintf(stderr, "Need same shape to have sum\n");
        exit(1);
    }

    Array *T = malloc(sizeof(Array));

    T->shape = malloc(2 * sizeof(int));

    for (int i = 0; i < 2; i++)
    {
        T->shape[i] = arr1->shape[i];
    }

    T->lines = malloc(T->shape[0] * sizeof(float *));

    for (int i = 0; i < T->shape[0]; i++)
    {
        void *ln = malloc(T->shape[1] * sizeof(float));
        T->lines[i] = ln;

        for (int j = 0; j < T->shape[1]; j++)
        {
           ((float *)T->lines[i])[j] = ((float *)arr1->lines[i])[j] + ((float *)arr2->lines[i])[j];

        }


    }

    return T;


}

/**
 * Function to multiply two matrix
 * 
 * @param arr1 first matrix
 * @param arr2 second matrix
 * 
 * @return dot result of the matrix multiplication
 */
Array* dot(Array *arr1, Array *arr2)
{
    /**
     * Verification if 2 matrix follow and is valid for multiplication 
     * The number of column on first matrix need to be equal on the number line of second matrix
     */
    if(arr1->shape[1] != arr2->shape[0]) {
        fprintf(stderr, "Can't to calculate dot");
        exit(1);
    }

    Array *dot = malloc(sizeof(Array));
    dot->shape = malloc(2 * sizeof(int));

    dot->shape[0] = arr1->shape[0];
    dot->shape[1] = arr2->shape[1];

    dot->lines = malloc(dot->shape[0] * sizeof(float *));

    for (int i = 0; i < dot->shape[0]; i++)
    {
        void *ln = malloc(dot->shape[1] * sizeof(float));
        dot->lines[i] = ln;

        for (int j = 0; j < dot->shape[1]; j++)
        {
            float sum_float = 0.0;

            for (int k = 0; k < arr1->shape[1]; k++)
            {
                sum_float += ((float *)arr1->lines[i])[k] * ((float *)arr2->lines[k])[j];
            }

            ((float *)dot->lines[i])[j] = sum_float;
        }

    }

    return dot;

}

/**
 * Function to get a matrix translation of a matrix
 * 
 * @param arr the matrix
 * 
 * @return t the translation of the matrix
 */
Array* T(Array *arr)
{
    Array *t = malloc(sizeof(Array));
    t->shape = malloc(2 * sizeof(int));
    t->shape[0] = arr->shape[1];
    t->shape[1] = arr->shape[0];

    t->lines = malloc(t->shape[0] * sizeof(float *));

    for (int i = 0; i < t->shape[0]; i++)
    {
        void *ln = malloc(t->shape[1] * sizeof(float));

        for (int j = 0; j < t->shape[1]; j++)
        {
            ((float *)ln)[j] = ((float *)arr->lines[j])[i];

        }

        t->lines[i] = ln;

    }

    return t;

}

/**
 * Function to create a mask of a matrix
 * 
 * @param arr the matrix source of mask
 * @param tp this is the type of mask (the definition is on numpy.h)
 * @param value
 * 
 * @return t masked array
 */
Array* mask(Array *arr, CoType tp, float value)
{
    Array *t = zeros_like(arr);

    for (int i = 0; i < arr->shape[0]; i++) {
        for (int j = 0; j < arr->shape[1]; j++) {
            switch (tp) {
                case BT:
                    if ((arr->lines[i])[j] >= value) (t->lines[i])[j] = 1.0;
                    break;
                case LT:
                    if ((arr->lines[i])[j] <= value) (t->lines[i])[j] = 1.0;
                    break;
                case EQ:
                    if ((arr->lines[i])[j] == value) (t->lines[i])[j] = 1.0;
                    break;

                default:
                    fprintf(stderr, "Undefined type of mask");
                    exit(1);

            }
        }
    }

    return t;
}

// ==================================================== //

void print_array(Array *arr)
{
    for (int i = 0; i < arr->shape[0]; i++)
    {
        for (int j = 0; j < arr->shape[1]; j++)
        {
            printf("%.2f ", ((float*)arr->lines[i])[j]);
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
