#include "stdio.h"
#define LIMIT 100

int main(int argc, char* argv[]) {
    FILE* file = fopen("task1.txt", "r");
    unsigned int index = 0;
    double data[LIMIT];

    if (file) {
        while (1) {
            if (fscanf(file, "%lf", &data[index]) == EOF) {
                break;
            }
            index++;
        }

        double sum = 0;

        for (auto i = 0; i < index; i++) {
            sum += *(data + i);
        }

        double average = sum / index;
        unsigned int count = 0;

        for (auto i = 0; i < index; i++) {
            if (*(data + i) < average) {
                count++;
            }
        }

        printf("%d\n", count);
    }

    fclose(file);
    return 0;
}