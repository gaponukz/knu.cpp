#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string encrypt(const string text) {
    string result;
    const string blacklist = ",./ -(){}!?:;";
 
    for (int i = 0; i < text.length(); i++) {
        if (blacklist.find(text[i]) != std::string::npos) {
            result += text[i];

        } else if (isupper(text[i])) {
            result += char(int(text[i] - 64) % 26 + 65);
            
        } else {
            result += char(int(text[i] - 96) % 26 + 97);
        }
    }

    return result;
}

int main(int argc, char** argv) {
    string data;
    ifstream file("task1.txt");

    string line;
    while (getline(file, line)) {
        data += line;
    }

    file.close();

    ofstream output;

    output.open ("task1.txt");
    output << encrypt(data);
    output.close();

    return 0;
}