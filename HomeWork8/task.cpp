#include "stdio.h"

const short int n = 2;
const short int m = 2;
const short int k = 2;

int main(int argc, char **argv) {
    int matrix1[n][m];
    int matrix2[m][k];
    int result_matrix[n][k];

    printf("Enter %dx%d matrix\n", n, m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("matrix[%d][%d] = ", i, j);
            scanf("%d", &matrix1[i][j]);
        }
    }

    printf("Enter %dx%d matrix\n", m, k);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            printf("matrix[%d][%d] = ", i, j);
            scanf("%d", &matrix2[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            result_matrix[i][j] = 0;

            for (int l = 0; l < k; l++) {
                result_matrix[i][j] += matrix1[i][l] * matrix2[l][j];
            }
        }
    }

    printf("Result matrix: \n");

    for (int row = 0; row < n; row++) {
        for(int columns = 0; columns < k; columns++) {
            printf("%d ", result_matrix[row][columns]);
        }
        printf("\n");
    }

    return 0;
}