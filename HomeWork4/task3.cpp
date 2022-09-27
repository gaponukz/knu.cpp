#include "stdio.h"
#define _USE_MATH_DEFINES
#include "math.h"

const double e = pow(10, -6);

double func() {
    double real_result = pow(M_PI, 4) / 90;
    double result = 0;
    double k = 1;

    do {
        result += + 1 / pow(k, 4);
        k += 1;
    } while (abs(real_result - result) > e);

    return result;
}

int main(int argc, char **argv) {
    printf("%lf\n", func());
    return 0;
}