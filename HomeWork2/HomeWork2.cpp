#include <cstdio>
#include <cmath>

double th(double x) {
	return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}

double th_derivative(double x) {
	return (exp(x) - exp(x)) * (exp(x) - exp(-x)) / pow((exp(x) + exp(-x)), 2) + 1;
}

int main() {
	double x = 4.0;

	printf("f(%.0lf) = %lf, f'(%.0lf) = %lf\n", x, th(x), x, th_derivative(x));
}
