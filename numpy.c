#include "numpy.h"

Array* array(void *data, int shape[], DType dtype)
{
    Array *arr = malloc(sizeof(Array));

    arr->shape = malloc(2 * sizeof(int));
    for (int k = 0; k < 2; k++)
    {
        arr->shape[k] = shape[k];
    }

    arr->dtype = dtype;

    size_t type_size;

    switch (arr->dtype)
    {
        case INT:
            type_size = sizeof(int);
            break;
        
        case FLOAT:
            type_size = sizeof(float);
            break;
    }
    
    arr->lines = malloc(shape[0] * sizeof(void *));

    int index = 0;

    for (int i = 0; i < shape[0]; i++)
    {
        void *ln = malloc(shape[1] * type_size);

        for (int j = 0; j < shape[1]; j++)
        {
            switch (dtype) {
                case INT:
                    ((int*)ln)[j] = ((int*)data)[j + index];
                    break;
                case FLOAT:
                    ((float*)ln)[j] = ((float*)data)[j + index];
                    break;
            }
        }

        arr->lines[i] = ln;
        index += shape[1];        

    }
    
    // printf("(%d, %d)\n", shape[0], shape[1]);
    return arr;
}


void* gen(int shape[], DType type, DataT dt) 
{
    size_t type_size;
    switch (type)
    {
        case INT: type_size = sizeof(int); break;
        case FLOAT: type_size = sizeof(float); break;
    }

    int dim = shape[0] * shape[1];
    void *data = malloc(dim * type_size);  

   if (type == INT) {
        int *ptr = data;
        for (int i = 0; i < dim; i++)
        {
            ptr[i] = dt.Int;
        }
    
   } else {
        float *ptr = data;
        for (int i = 0; i < dim; i++)
        {
            ptr[i] = dt.Float;
        }
        
   }

    return data;
    
}

Array* ones(int shape[], DType type) 
{
    DataT dt;
    dt.Int = 1;
    dt.Float = 1.0;

    void * data = gen(shape, type, dt);

    return array(data, shape, type);
    
}

Array* zeros(int shape[], DType type) 
{

    DataT dt;
    dt.Int = 0;
    dt.Float = 0.0;

    void * data = gen(shape, type, dt);

    return array(data, shape, type);
    
}

Array* zeros_like(Array *arr)
{
    return zeros(arr->shape, arr->dtype);
}

void print_array(Array *arr)
{
    for (int i = 0; i < arr->shape[0]; i++)
    {
        for (int j = 0; j < arr->shape[1]; j++)
        {
            switch (arr->dtype)
            {
                case INT:    printf("%2d ", ((int*)arr->lines[i])[j]); break;
                case FLOAT:  printf("%.2f ", ((float*)arr->lines[i])[j]); break;
            }
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