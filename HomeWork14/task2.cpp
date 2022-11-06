#include <iostream>
#include <string>
#include <fstream>

using namespace std;

uint32_t get_empty_lines_count(string filename) {
    string line;
    uint32_t count = 0;
    ifstream file(filename);

    while (getline (file, line)) {
        if (line == "") {
            count++;
        }
    }

    file.close();
    return count;
}

uint32_t get_max_line_length(string filename) {
    string line;
    uint32_t max = 0;
    ifstream file(filename);

    while (getline (file, line)) {
        uint32_t length = line.length();

        if (length > max) {
            max = length;
        }
    }

    file.close();
    return max;
}

int main(int argc, char **argv) {
    cout << get_empty_lines_count("task2.txt") << endl;
    cout << get_max_line_length("task2.txt") << endl;

    return 0;
}
