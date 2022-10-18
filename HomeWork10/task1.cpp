#include "stdio.h"

typedef struct {
    unsigned int amount;
    unsigned int coin_amount;
} Price;

void print(Price price) {
    printf("%d.%d\n", price.amount, price.coin_amount);
}

Price input() {
    Price price;
    scanf("%d.%d", &price.amount, &price.coin_amount);
    return price;
}

int main(int argc, char* argv[]) {
    Price price = input();

    price.amount += 50;

    print(price);
}