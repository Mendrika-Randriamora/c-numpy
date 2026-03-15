#include "numpy.h"
#include <threads.h>

Array* array(float *data, int shape[])
{
    Array *arr = malloc(sizeof(Array));

    arr->shape = malloc(2 * sizeof(int));
    for (int k = 0; k < 2; k++)
    {
        arr->shape[k] = shape[k];
    }

    arr->lines = malloc(shape[0] * sizeof(float *));

    int index = 0;

    for (int i = 0; i < shape[0]; i++)
    {
        void *ln = malloc(shape[1] * sizeof(float));

        for (int j = 0; j < shape[1]; j++)
        {

            ((float*)ln)[j] = ((float*)data)[j + index];
        }

        arr->lines[i] = ln;
        index += shape[1];

    }

    return arr;
}


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

Array* ones(int shape[])
{
    void * data = gen(shape, 1.0);

    return array(data, shape);

}

Array* zeros(int shape[])
{
    void * data = gen(shape, 0.0);

    return array(data, shape);

}

Array* zeros_like(Array *arr)
{
    return zeros(arr->shape);
}

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

Array* sum(Array *arr1, Array *arr2)
{
    if (arr1->shape[0] != arr2->shape[0] || arr1->shape[1] != arr2->shape[1]) {
        fprintf(stderr, "Need same shape to have sum");
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


Array* dot(Array *arr1, Array *arr2)
{
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
