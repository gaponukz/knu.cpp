#include <iostream>
#include <cstring>
#include <algorithm>
#define ASCII_SIZE 256
#define BAD_CHARS_COUNT 26

using namespace std;

char asciitolower(char in) {
    return in <= 'Z' && in >= 'A' ? in - ('Z' - 'z') : in;
}

char max_char(string str) {
    int count[ASCII_SIZE] = { 0 };
    int len = str.length();
    int max = 0;
    char result;
 
    for (int i = 0; i < len; i++) {
        count[str[i]]++;

        if (max < count[str[i]]) {
            max = count[str[i]];
            result = str[i];
        }
    }
 
    return result;
}

int main(int argc, char **argv) {
    string str = "Okey, we need to test this program.";

    transform(str.begin(), str.end(), str.begin(), asciitolower);

    const char chars[BAD_CHARS_COUNT] = "qwrtpsdfghklzxcvbnm,.;:- ";

    for (unsigned int i = 0; i < BAD_CHARS_COUNT; ++i) {
        str.erase(std::remove(str.begin(), str.end(), chars[i]), str.end());
    }

    cout << max_char(str) << endl;
}