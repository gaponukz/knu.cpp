#include "stdio.h"
#include "math.h"

float function(int x) {
	return exp(-(x ^ 2));
}

float function1(int x) {
	return sqrt(x);
}

int main() {
	const int table_size = 5;
	
	printf("x----|");

	for (int i = 0; i <= table_size; i++) {
		printf("--%i-|", i);
	}
	printf("\n-----|");
	
	for (int i = 0; i <= table_size; i++) {
		printf("----|");
	}
	printf("\nF(x) |");

	for (int i = 0; i <= table_size; i++) {
		printf("%.02f|", function(i));
	}
}