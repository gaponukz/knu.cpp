#include <iostream>
#include <fstream>
#include <string>
#define ALPHABET_COUNT 26

using namespace std;

int main(int argc, char** argv) {
    string data;
    char alphabet[ALPHABET_COUNT];
    ifstream file("task1.txt");

    string line;
    while (getline(file, line)) {
        data += line;
    }

    file.close();

    unsigned short int index = 0;

    for (char l = 'a'; l <= 'z'; ++l) {
        alphabet[index] = l;
        index++;
    }
    
    for (auto i = 0; i < data.length(); i++) {
        for (auto j = 0; j < ALPHABET_COUNT; j++) {
            if (data[i] == alphabet[j]) {
                cout << "here" << endl;
                if (j != ALPHABET_COUNT) {
                    data[i] = alphabet[j+1];
                } else {
                    data[i] = alphabet[0];
                }
            }
        }
    }

    cout << data << endl;

    return 0;
}