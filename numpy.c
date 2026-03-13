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

Array* eye(int shape[], DType type)
{
    if (shape[0] != shape[1]) {
        fprintf(stderr, "Eye matrix need a square matrix");
        exit(1);
    }
    DataT dt;
    dt.Int = 1;
    dt.Float = 1.0;

    Array* temp = zeros(shape, type);

    for (int i = 0; i < shape[0]; i++)
    {
        switch (type)
        {
            case INT:
               ((int *)temp->lines[i])[i] = dt.Int;
                break;
            
            case FLOAT:
                ((float *)temp->lines[i])[i] = dt.Float;
        }
    }
    
    return temp;
}

// ================= Arithmetic ======================= //

void add_nbr(Array *arr, int a, float b)
{
    if (a != 0 && b == 0.0 && arr->dtype == INT) {
        for (int i = 0; i < arr->shape[0]; i++)
        {
            for (int j = 0; j < arr->shape[1]; j++)
            {
                ((int *)arr->lines[i])[j] += a;
            }
            
        }
        
    } else if (b != 0.0 && a == 0 && arr->dtype == FLOAT)
    {
        for (int i = 0; i < arr->shape[0]; i++)
        {
            for (int j = 0; j < arr->shape[1]; j++)
            {
                ((float *)arr->lines[i])[j] += b;
            }
            
        }
        
    }
    
}

Array* sum(Array *arr1, Array *arr2)
{
    if (arr1->shape[0] != arr2->shape[0] || arr1->shape[1] != arr2->shape[1]) {
        fprintf(stderr, "Need same shape to have sum");
        exit(1);
    }

    DType type;

    if (arr1->dtype == FLOAT || arr2->dtype == FLOAT)
        type = FLOAT;
    else    
        type = INT;

    size_t type_size = (type == INT) ? sizeof(int) : sizeof(float);

    Array *T = malloc(sizeof(Array));
    T->dtype = type;

    T->shape = malloc(2 * sizeof(int));

    for (int i = 0; i < 2; i++)
    {
        T->shape[i] = arr1->shape[i];
    }
    
    T->lines = malloc(T->shape[0] * sizeof(void *));

    for (int i = 0; i < T->shape[0]; i++)
    {
        void *ln = malloc(T->shape[1] * type_size);
        T->lines[i] = ln;

        for (int j = 0; j < T->shape[1]; j++)
        {
            switch (T->dtype)
            {
                case INT: 
                    ((int *)T->lines[i])[j] = ((int *)arr1->lines[i])[j] + ((int *)arr2->lines[i])[j];
                    break;

                case FLOAT:
                    ((float *)T->lines[i])[j] = ((float *)arr1->lines[i])[j] + ((float *)arr2->lines[i])[j];
                    break;
            }
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

    if(arr1->dtype == FLOAT || arr2->dtype == FLOAT)
        dot->dtype = FLOAT;
    else    
        dot->dtype = INT;

    size_t type_size = (dot->dtype == INT) ? sizeof(int) : sizeof(float);
    
    dot->lines = malloc(dot->shape[0] * sizeof(void *));

    for (int i = 0; i < dot->shape[0]; i++)
    {
        void *ln = malloc(dot->shape[1] * type_size);
        dot->lines[i] = ln;

        for (int j = 0; j < dot->shape[1]; j++)
        {
            int sum_int = 0;
            float sum_float = 0.0;

            for (int k = 0; k < arr1->shape[1]; k++)
            {
                switch (dot->dtype)
                {
                    case INT:
                        sum_int += ((int *)arr1->lines[i])[k] * ((int *)arr2->lines[k])[j];
                        break;
                    case FLOAT:
                        sum_float += ((float *)arr1->lines[i])[k] * ((float *)arr2->lines[k])[j];
                        break;
                    }
            }

            switch (dot->dtype)
            {
                case INT:
                    ((int *)dot->lines[i])[j] = sum_int;
                    break;
                case FLOAT:
                    ((float *)dot->lines[i])[j] = sum_float;
                    break;
            }
            
        }
        
    }
    printf("(%d, %d)\n", dot->shape[0], dot->shape[1]);
    return dot;
    
} 

Array* T(Array *arr)
{
    Array *t = malloc(sizeof(Array));
    t->shape = malloc(2 * sizeof(int));
    t->shape[0] = arr->shape[1];
    t->shape[1] = arr->shape[0];
    t->dtype = arr->dtype;

    size_t type_size = (arr->dtype == INT) ? sizeof(int) : sizeof(float);

    t->lines = malloc(t->shape[0] * sizeof(void *));

    for (int i = 0; i < t->shape[0]; i++)
    {
        void *ln = malloc(t->shape[1] * type_size);

        for (int j = 0; j < t->shape[1]; j++)
        {
            switch (t->dtype)
            {
                case INT:
                    ((int *)ln)[j] = ((int *)arr->lines[j])[i];
                    break;
                case FLOAT:
                    ((float *)ln)[j] = ((float *)arr->lines[j])[i];
                    break;
            }
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