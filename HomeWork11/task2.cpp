#include "stdio.h"
#include "string.h"
#define LIMIT 100

struct Toy {
    char name[LIMIT];
    double price;
    unsigned int from_year_old;
    unsigned int to_year_old;
};

void print_toy(Toy toy) {
    printf("Toy %s, price:%lf (from %d to %d)\n", toy.name, toy.price, toy.from_year_old, toy.to_year_old);
}

Toy input_toy() {
    Toy toy;
    scanf("%100s %lf %d %d", &toy.name, &toy.price, &toy.from_year_old, &toy.to_year_old);

    return toy;
}

bool compare_toy(Toy toy1, Toy toy2) {
    return (strcmp(toy1.name, toy2.name) == 0) && (toy1.price == toy2.price) && (toy1.from_year_old == toy2.from_year_old) && (toy1.to_year_old == toy2.to_year_old);
}

int append_toy(Toy toy) {
    FILE* file = fopen("task2.txt", "a");

    if (!file) {
        fclose(file);
        return 0;
    }

    fprintf(file, "\n%s %lf %d %d", toy.name, toy.price, toy.from_year_old, toy.to_year_old);
    fclose(file);

    return 1;
}

int main(int argc, char* argv[]) {
    FILE* file = fopen("task2.txt", "r");
    unsigned int index = 0;
    Toy data[LIMIT];

    if (file) {
        while (1) {
            if (fscanf(file, "%100s %lf %d %d",
                &data[index].name, &data[index].price,
                &data[index].from_year_old, &data[index].to_year_old
            ) == EOF) {
                break;
            }
            index++;
        }
        fclose(file);

        Toy user_toy = input_toy();
        bool find = false;

        for (auto i = 0; i < index; i++) {
            if (compare_toy(user_toy, *(data + i))) {
                find = true;
                printf("Find!\n");
                // print_toy(*(data + i));
                break;
            }
        }

        if (!find) {
            if (!append_toy(user_toy)) {
                printf("Can not add toy to file\n");
            } else {
                printf("Add new toy\n");
            }
        }
    }

    return 0;
}
