#include "stdio.h"
#include "math.h"

int main() {
	for (int i = 0; i <= 10000; i++) {
		printf("%i - %20.4lf\n", i, pow(i, 8));
	}
}