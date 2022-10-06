#include "stdio.h"
#include "math.h"
#define SIZE 5

bool is_perfect_square(unsigned int x) {
    int square = (int)(sqrt(x));

    return square * square == x;
}

bool is_fibonacci(unsigned int number) {
    return is_perfect_square(5 * number * number + 4) || is_perfect_square(5 * number * number - 4);
}

int main(int argc, char **argv) {
    unsigned int array[SIZE];
    unsigned int result = 0;

    for (int i = 0; i < SIZE; i++) {
        scanf("%d", &array[i]);
    }

    for (int i = 0; i < SIZE; i++) {
        if (is_fibonacci(*(array + i))) {
            result += 1;
        }
    }

    printf("fibo count: %d\n", result);
}