#include "numpy.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_matrix_valide(unsigned int shape[3], float *data, size_t len_data) {
    if (shape[0] <= 0 || shape[1] <= 0 || shape[2] <= 0) {
        return false;
    }

    return len_data == (shape[0] * shape[1] * shape[2]);
}

Matrix *new_matrix(char name[], unsigned int shape[3], float *data, size_t len_data) {

    if(!is_matrix_valide(shape, data, len_data)) {
        fprintf(stderr, "Matrix format not valid !!\n");
        exit(1);
    }

    Matrix *new = malloc(sizeof(Matrix));
    strcpy(new->name, name);

    for (int i = 0; i < 3; i++) {
        new->shape[i] = shape[i];
    }

    new->data = malloc(len_data * sizeof(float));
    new->data = data;


    return new;
}

void shape(Matrix *m) {
    char *tr[] = {"width", "height", "level"};
    size_t ln = 3;

    printf("+-----------------------------+\n");
    printf("| Shape Info For: %10s  |\n", m->name);
    printf("+-----------------------------+\n");
    for (int i = 0; i < 3; i++) {
        printf("|%10s   : %5d         |\n", tr[i], m->shape[i]);
    }
    printf("+-----------------------------+\n");
}

void view(Matrix *m) {
    int w = m->shape[0];
    int h = m->shape[1];
    int l = m->shape[2];
    printf("w = %d, h = %d, l = %d\n", w, h, l);
    printf("\n");

    for (int il = 0; il < l; il++) {
        int k = 0;
        for(int i = il; i < w*h*h; i = i + 2) {
            printf("%.2f ", m->data[i], k);
            if (k == w - 1) printf("\n");
            k++;
        }
        printf("\n------------\n");
    }
}
