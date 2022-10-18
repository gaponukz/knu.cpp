#include "stdio.h"
#define LIMIT 100

typedef struct {
    char lastname[LIMIT];
    unsigned int group_number;
    short int ratings[3];
} StudentInfo;

void print_info(StudentInfo info) {
    printf(
        "Student %s in group #%d with rating [%d, %d, %d]\n",
        info.lastname, info.group_number, info.ratings[0], info.ratings[1], info.ratings[2]
    );
}

int main(int argc, char **argv) {
    const unsigned int number_of_students =  4;

    StudentInfo database[number_of_students] = {
        {"Max", 1, {5, 4, 3}},
        {"Ana", 2, {2, 5, 4}},
        {"Adam", 2, {5, 2, 3}},
        {"Aster", 1, {5, 5, 5}},
    };

    // 16.a
    for (int i = 0; i < number_of_students; i++) {
        for (int j = 0; j < 3; j++) {
            if (database[i].ratings[j] <= 2) {
                print_info(database[i]);
                break;
            }
        }
    }


    // 16.v
    const unsigned short int good_rating = 4;

    for (int i = 0; i < number_of_students; i++) {
        bool good_student = true;

        for (int j = 0; j < 3; j++) {
            if (database[i].ratings[j] <= good_rating) {
                good_student = false;
                break;
            }
        }

        if (good_student) {
            print_info(database[i]);
        }
    }
}