#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class ValueError: public logic_error {
    public: ValueError(const string& message): logic_error(message) {}
};

void assert(string str, int base) {
    if (base > 16) {
        throw ValueError("Base must be between 2 and 16");
    }
 
    else if (base <= 10) {
        for (int i = 0; i < str.length(); i++) {
            if (!(str[i] >= '0' && str[i] < ('0' + base))) {
                throw ValueError("Not in base");
            }
        }
    } else {
        for (int i = 0; i < str.length(); i++) {
            if (! ((str[i] >= '0' && str[i] < ('0' + base)) || (str[i] >= 'A' && str[i] < ('A' + base - 10)))) {
                throw ValueError("Not in base");
            }
        }
    }
}

int val(char c) {
    if (c >= '0' && c <= '9') {
        return (int)c - '0';
    }
    
    return (int)c - 'A' + 10;
}

int toDeci(string str, int base) {
    int len = str.size();
    int power = 1;
    int num = 0;
 
    for (int i = len - 1; i >= 0; i--) {
        if (val(str[i]) >= base) {
            printf("Invalid Number");
            return -1;
        }

        num += val(str[i]) * power;
        power = power * base;
    }
 
    return num;
}

char reVal(int num) {
    if (num >= 0 && num <= 9) {
        return (char)(num + '0');
    }

    return (char)(num - 10 + 'A');
}

string fromDeci(int base, int inputNum) {
    string res = "";

    while (inputNum > 0) {
        res += reVal(inputNum % base);
        inputNum /= base;
    }

    reverse(res.begin(), res.end());
 
    return res;
}
 
void convertBase(string s, int a, int b) {
    assert(s, a);

    int num = toDeci(s, a);
    string ans = fromDeci(b, num);

    cout << ans << endl;
}

int main(int argc, char** argv) {
    convertBase("AF87", 16, 10);

    try {
        convertBase("123", 2, 10);
    } catch (const ValueError error) {
        cout << error.what() << endl;
    }

    return 0;
}
