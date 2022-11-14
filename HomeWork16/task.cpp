#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class World {
    protected:
    
    string prefix;
    string second_prefix;
    string root;
    string suffix;
    string end;

    public:

    World() {}
    World(string prefix, string second_prefix, string root, string suffix, string end) {
        this->prefix = prefix;
        this->second_prefix = second_prefix;
        this->root = root;
        this->suffix = suffix;
        this->end = end;
    }

    void set_prefix(string prefix) { this->prefix = prefix; }

    string get_prefix() { return this->prefix; }

    void set_second_prefix(string second_prefix) { this->second_prefix = second_prefix; }

    string get_second_prefix() { return this->second_prefix; }

    void set_root(string root) { this->root = root; }

    string get_root() { return this->root; }

    void set_suffix(string suffix) { this->suffix = suffix; }
    
    string get_suffix() { return this->suffix; }

    void set_end(string end) { this->end = end; }

    string get_end() { return this->end; }

};

// https://englishprime.ua/uk/padezhi-v-anglijskom/

class Verb: public World {
    public:

    string gender(string gender = "male") {}

    string plural() {}

    string singular() {}

    string third() {}

    string word_case(string _case) {
        if (_case == "common") { }
        else if (_case == "genetive") {}
        else if (_case == "davite") {}
        else if (_case == "ablative") {}
        else if (_case == "possessive") {}
    }
};

class Noun : public World {
    public:

    string gender(string gender = "male") {}

    string plural() {}

    string singular() {}

    string third() {}

    string word_case(string _case) {
        if (_case == "common") { }
        else if (_case == "genetive") {}
        else if (_case == "davite") {}
        else if (_case == "ablative") {}
        else if (_case == "possessive") {}
    }
};

class Adjecvite : public World {
    public:

    string gender(string gender = "male") {}

    string plural() {}

    string singular() {}

    string third() {}

    string word_case(string _case) {
        if (_case == "common") { }
        else if (_case == "genetive") {}
        else if (_case == "davite") {}
        else if (_case == "ablative") {}
        else if (_case == "possessive") {}
    }
};

int main(int argc, char** argv) {
    return 0;
}