#include "stdio.h"

unsigned int get_left_one_bit(unsigned int number) {
    int result_index = -1;
    int _number;

    while (true) {
        _number = number & 1;
        result_index++;

        if (_number == 1) {
            break;
        }

        number = number >> 1;
    }

    return result_index;
}

unsigned int get_left_zero_bit(int number) {
    int result_index = -1;
    const int a = 128 << 8;
    int _number;

    while (true) {
        _number = number & a;
        result_index++;

        if (_number == a) {
            break;
        }

        number = number << 1;
    }
    return result_index;
}

int main(int argc, char **argv) {
    const short number = 2;

    printf("left one index of %d is %d\n", number, get_left_one_bit(number));
    printf("left zero index of %d is %d\n", number, get_left_zero_bit(number));
    return 0;
}