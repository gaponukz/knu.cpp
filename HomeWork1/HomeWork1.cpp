#include <stdio.h>

int main() {
    double T = 365.0 + 1.0 / (4.0 + (1.0 / (7.0 + 1.0 / (1.0 + 1.0 / 3.0))));
    
    printf("T = %lf\n", T);
}