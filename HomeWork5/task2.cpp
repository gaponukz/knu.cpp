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

double a(double k);

double b(double k) {
    if (k == 1) {
        return 1;
    }
    if (k == 2) {
        return 0;
    }

    return 2 * b(k - 1) + a(k - 1);
}

double a(double k) {
    if (k == 1) {
        return 2;
    }
    if (k == 2) {
        return 1;
    }

    return a(k-1) / (k + 1) + a(k - 2) + b(k); // original a(k), but it is not working, fix to a(k-1)
}

double function(unsigned int n) {
    double result = 0;

    for (int k = 1; k <= n; k++) {
        result += _pow(3, 2 * k + 1) / a(k) * b(k) + 1;
    }

    return result;
}

int main(int argc, char **argv) {
    const unsigned int n = 3;

    printf("S(%d) = %lf", n, function(n));
    return 0;
}
