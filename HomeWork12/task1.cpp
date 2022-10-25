#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    uint32_t numbers_to_input;

    cout << "Numbers count: ";
    cin >> numbers_to_input;

    double* array = new double[numbers_to_input];

    for (auto i = 0; i < numbers_to_input; i++) {
        cin >> array[i];

        if (i != numbers_to_input - 1) {
            cin.ignore(256, ',');
        }
    }

    cout.width(5);

    for (int i = 0; i < numbers_to_input; i++) {
        if (*(array + i) > 0) {
            double log_result = log(*(array + i));

            cout << scientific << log_result << endl;
            cout << dec << log_result << endl;
        } else {
            cout << "None" << endl;
        }
    }

    return 0;
}