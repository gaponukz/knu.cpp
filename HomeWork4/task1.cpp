#include "stdio.h"
#include "math.h"

double func(double x, unsigned int n) {
    double result = 0;

    for (double i = 1; i < n; i++) {
        result += pow(x, pow(2, n - i));
    }

    return result;
}

int main(int argc, char **argv) {
    printf("%f\n", func(2.5, 4));

    return 0;
}