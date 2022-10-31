#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv) {
    string input = "1 2  3 4    5 6";
    size_t pos = input.find("  ");

    // remove all double spaces
    while (pos != string::npos) {
        input.replace(pos, 2, " ");
        pos = input.find("  ", pos);
    }

    // replace all spaces to coma
    pos = input.find(" ");

    while (pos != string::npos) {
        input.replace(pos, 1, ",");
        pos = input.find(" ", pos);
    }

    // add dot
    input += ".";
    
    cout << input << endl;

    return 0;
}