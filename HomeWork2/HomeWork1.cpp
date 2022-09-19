#include <cstdio>
#include <cmath>
// #define _USE_MATH_DEFINES
# define M_PI 3.14159265358979323846  /* pi */

double distance(double x1, double y1, double x2, double y2) {
    return hypot(x2 - x1, y2 - y1);
}

double square(double r, double r_big) {
    return M_PI * r * r_big / 4;
}

int main() {
    double r_x1, r_y1, r_x2, r_y2;
    double rbig_x1, rbig_y1, rbig_x2, rbig_y2;
    
    printf("r_x1 = ");
    scanf_s("%lf", &r_x1);

    printf("r_y1 = ");
    scanf_s("%lf", &r_y1);
 
    printf("r_x2 = ");
    scanf_s("%lf", &r_x2);

    printf("r_y2 = ");
    scanf_s("%lf", &r_y2);
    
    printf("rbig_x1 = ");
    scanf_s("%lf", &rbig_x1);

    printf("rbig_y1 = ");
    scanf_s("%lf", &rbig_y1);

    printf("rbig_x2 = ");
    scanf_s("%lf", &rbig_x2);

    printf("rbig_y2 = ");
    scanf_s("%lf", &rbig_y2);

    printf("elipce square = %lf", square(
        distance(r_x1, r_y1, r_x2, r_y2),
        (rbig_x1, rbig_y1, rbig_x2, rbig_y2)
    ));
}