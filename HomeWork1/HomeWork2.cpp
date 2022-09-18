#include "stdio.h"
#include "math.h"

int main() {
    double input_number;
    printf("number = ");
    scanf_s("%lf", &input_number);

    printf("log10(%lf) = %.3lf", input_number, log10(input_number));
}