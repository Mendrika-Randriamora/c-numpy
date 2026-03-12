#ifndef ADD_H
#define ADD_H

#include <stdio.h>
#include <stdlib.h>

int* range(int n)
{
    int *t = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        *(t + i) = i;
    }
    return t;
}

#endif