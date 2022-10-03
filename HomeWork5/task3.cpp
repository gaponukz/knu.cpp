#include "stdio.h"
#include "math.h"

double _pow(int x, int y) {
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

double number(double n) {
    return n == 1 ? 0.5 : (n / (n + 1))  * number(n - 2);
}

double factor_fraction(double x, long double e) {
    double last = 1, current = 1, step = 0;
    double _number;

    double index = 1;
    double jndex = 0;

    do {
        step = _pow(-1, index) * number(index + jndex) * _pow(x, index);
        last = current;
        current += step;
        printf("%lf\n", current);
        index++;
        jndex++;
    } while (abs(last - current) > e);

    return current;
}

int main(int argc, char **argv) {
    const double x = 1;
    const double e = 0.01;

    printf("f(%lf) = %lf\n", x, factor_fraction(x, e));
    return 0;
}