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

unsigned int factorial(unsigned int n) {
    return n == 0 || n == 1 ? 1 : n * factorial(n - 1);
}

double a(double k) {
    return k == 0 ? 1 : k * a(k - 1) + 1/k;
}

double function(unsigned int n) {
    double result = 0;

    for (int k = 0; k < n; k++) {
        result += (_pow(2, k)) / (factorial(k));
    }

    return result;
}

int main(int argc, char **argv) {
    const unsigned int n = 5;

    printf("S(%d) = %lf", n, function(n));
    return 0;
}