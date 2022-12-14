#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    ifstream file;
    ofstream output;
    file.open("task2_input.txt");
    output.open("task2_output.txt");

    while (!file.eof()) {
        double number;

        file >> number;

        if (-1 <= number <= 1) {
            output << scientific << asin(number) << endl;
        }

        if (!file.good()) {
            break;
        } else {
            file.ignore(256, ';');
        }
    }

    file.close();
    output.close();
}