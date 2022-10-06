#include <stdio.h>
#include <math.h>

double _pow(double x, int y) {
    double res = 1;

    for (int i = 1; i <= y; i++){
        res *= x;
    }

    return res;
}

double function(double x, double e) {
    double current;
    double last;
    double index;

    do {} while (abs(last - current) > e);
}

int main(int argc, char **argv){
    
    return 0;
}