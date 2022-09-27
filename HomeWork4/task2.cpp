#include "stdio.h"

unsigned long _pow(int x, int y) {
    long number = 1;

    while (y) {
        if (y & 1) {
            number = number * x;
        }

        y >>= 1;
        x = x * x;
    }

    return number;
}

unsigned long _factorial(unsigned int n) {
    return n == 1 || n == 0 ? 1 : n * _factorial(n - 1);
}

double func(double x, unsigned int k) {
    double result = 0;

    for (double i = 1; i < k; i++) {
        result += (_pow(-1, i) * _pow(x, 2 * k + 1)) / _factorial(2 * i + 1);
    }

    return result;
}

int main (int argc, char **argv) {
    printf("%f\n", func(2.5, 10));

    return 0;
}