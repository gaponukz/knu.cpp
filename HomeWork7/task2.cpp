#include "stdio.h"
#define SIZE 5

double max_odd_index_number(double *_array, int _count) {
    double maximum = _array[0];
    int index = 2;

    while (index < _count) {
        if (maximum < _array[index]) {
            maximum = _array[index];
        }

        index += 2;
    }

    return maximum;
}

int main(int argc, char **argv) {
    double array[SIZE];

    for (int i = 0; i < SIZE; i++) {
        scanf("%lf", &array[i]);
    }

    printf("%lf\n", max_odd_index_number(array, SIZE));

}