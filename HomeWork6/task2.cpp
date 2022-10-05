#include "stdio.h"

unsigned int get_left_bit_possition(int number) {
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

unsigned int swap_bits(unsigned short number) {
    const int left_bit_possition = get_left_bit_possition(number);

    number <<= 1;

    int bn = number & 1;
    int bm = number & ( 1 << left_bit_possition);

    number = number & (~1) & (~(1 << left_bit_possition));
    if (bn) number = number | (1 << left_bit_possition);
    if (bm) number = number | 1;

    return number;
}

int main() {
    printf("%d\n", swap_bits(130));
}