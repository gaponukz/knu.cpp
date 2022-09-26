#include "stdio.h"
#include "math.h"

// 3.23a

double onestep(double x) {
    return x < 0 ? 0 : 1;
}

int main(int argc, char **argv) {
    const double x = -10;

    printf("onestep(%lf) = %0.lf\n", x, onestep(x));
    printf("onestep'(%lf) = 0\n", x);
    return 0;
}