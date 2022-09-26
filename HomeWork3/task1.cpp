#include "stdio.h"
#include "math.h"

// 3.13a

int main(int argc, char **argv) {
    double a1, b1, c1;
    double a2, b2, c2;

    scanf("%lf", &a1);
    scanf("%lf", &b1);
    scanf("%lf", &c1);
    scanf("%lf", &a2);
    scanf("%lf", &b2);
    scanf("%lf", &c2);

    if (a1 / a2 == b1 / b2 == c1 / c2) {
        printf("inf\n");
        
    } else if (a1 / a2 == b1 / b2 != c1 / c2) {
        printf("none\n"); 

    } else {
        double x = ((b2*c1/b1) - c2) / (a2 - (b2 * a1 / b1));
        double y = - (a1 * x + c1) / b1;

        printf("x = %f, y = %f\n", x, y);
    }

    return 0;
}