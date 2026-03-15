#ifndef ADD_H
#define ADD_H

#include <stdio.h>
#include <stdlib.h>

float* range(int n)
{
    float *t = (float *)malloc(n * sizeof(float));

    for (int i = 0; i < n; i++)
    {
        *(t + i) = i;
    }
    return t;
}

float* linspace(int from, int to, int n)
{
    float *t = (float *)malloc(n * sizeof(float));

    float step = ((float)(to - from) / n);

    int i = 0;
    float j = (float)from;

    while (i < n && j < to)
    {
        *(t + i) = j;
        i++;
        j += step;
    }

    return t;
}

#endif
