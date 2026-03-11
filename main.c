#include <stdio.h>
#include "numpy.h"

int main()
{
    Array *arr;
    int shape[] = {2, 3};
    int data[] = {1, 2, 3, 4, 5, 6};

    printf("Array 1 : \n");
    arr = array(data, shape, INT);

    print_array(arr); 

    printf("============\n");
    printf("Array 2 : \n");
    int shape1[] = {2, 2};
    float data1[] = {2.1, 2.2, 2.3, 2.4};

    Array *arr1 = array(data1, shape1, FLOAT);

    print_array(arr1);
    
    free_array(arr);
    free_array(arr1);

    return 0;
}