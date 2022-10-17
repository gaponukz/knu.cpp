#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <stdio.h>
#include <string.h>

#define NUMBER_LIMIT 21

double** create_matrix(unsigned int n, unsigned int m) {
    double **matrix = (double**)calloc(n, sizeof(*matrix));

    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)calloc(m, sizeof(*matrix[i]));

        for (int j = 0; j < m; j++) {
            matrix[i][j] = (double)(rand() % NUMBER_LIMIT);
        }
    }
    
    return matrix;
}

void delete_matrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void print_matrix(double** matrix, unsigned int n, unsigned int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    unsigned int n = 2, m = 3, k;
    double **matrix = create_matrix(n, m);
    print_matrix(matrix, n, m);

    printf("k = ");
    scanf("%d", &k);

    // insert zero vector after k matrix row
    if (n > k) {
        double** old = create_matrix(n, m);
        memcpy(old, matrix, sizeof(double) * n * m);

        matrix = (double**)realloc(matrix, (n + 1) * sizeof(*matrix));

        for (int i = 0; i < n+1; i++) {
            matrix[i] = (double*)calloc(m, sizeof(double) * n * m);
        }

        for (int i = 0; i < n+1; i++) {
            for (int j = 0; j < m; j++) {
                if (i == k + 1) {
                    matrix[i][j] = 0;
                } else if (i > k) {
                    matrix[i][j] = old[i-1][j];
                } else {
                    matrix[i][j] = old[i][j];
                }
            }
        }

    }

    print_matrix(matrix, n + 1, m);

    return 0;
}