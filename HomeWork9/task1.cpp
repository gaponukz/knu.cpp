#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int main(int argc, char **argv) {
    int length;

    while(true) {
        printf("vector length = ");
        scanf("%d", &length);

        if (length == 0) {
            break; 
        }

        double* vector = (double*)malloc(length * sizeof(*vector));
        double sum = 0;

        for (int i = 0; i < length; i++) {
            printf("vector[%d] = ", i);
            scanf("%lf", &vector[i]);

            sum += *(vector + i);
        }

        double average = (double)(sum / length);

        printf("average = %f\n", average);

        for (int i = 0; i < length; i++) {
            printf("%lf ", fabs(*(vector + i) - average));
        }

        printf("\n");
        free(vector);
    }
}