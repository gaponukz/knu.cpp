#include <iostream>
#include <string>

using namespace std;

class Word {
    protected:
    
    string prefix;
    string second_prefix;
    string root;
    string suffix;
    string end;

    public:

    Word() {}
    Word(string root) { this->root = root; }
    Word(string prefix, string second_prefix, string root, string suffix, string end) {
        this->prefix = prefix;
        this->second_prefix = second_prefix;
        this->root = root;
        this->suffix = suffix;
        this->end = end;
    }

    string get_word() {
        return this->prefix + this->second_prefix + this->root + this->suffix + this->end;
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

    friend ostream& operator<<(ostream& os, Word &Word) {
        os << Word.get_word();
        return os;
    }

};

class Verb: public Word {
    public:
    using Word::Word;

    void plural() {
        this->set_end("s");
    }

    void singular() {
        this->set_end("");
    }

    void third() {
        this->set_end("es");
    }
};

class Noun : public Word {
    private:
    bool is_plural = false;

    public:

    using Word::Word;

    void plural() {
        this->is_plural = true;
        this->set_end("s");
    }

    void singular() {
        this->is_plural = false;
        this->set_end("");
    }

    void to_word_case(string _case) {
        if (_case == "common") {
            this->set_end("");
        } else if (_case == "possessive") {
            if (!this->is_plural) {
                this->set_end("'s");

            } else {
                this->set_end("s'");
            }
        }
    }
};

class Adjective : public Word {
    public:

    using Word::Word;

    void comparison_first() {
        this->set_suffix("");
        this->set_end("");
    }

    void comparison_second() {
        size_t root_length = this->get_root().length();
        this->set_suffix(string(1, this->get_root()[root_length-1]));
        this->set_end("er");
    }

    void comparison_max() {
        size_t root_length = this->get_root().length();
        this->set_suffix(string(1, this->get_root()[root_length-1]));
        this->set_end("est");
    }
};

int main(int argc, char** argv) {
    Adjective adjective("big");
    adjective.comparison_second();
    cout << adjective << endl;
    adjective.comparison_max();
    cout << adjective << endl;
    adjective.comparison_first();
    cout << adjective << endl;

    Verb verb("enjoy");
    verb.plural();
    cout << verb << endl;
    verb.singular();
    cout << verb << endl;

    Noun noun("teacher");
    noun.plural();
    cout << noun << endl;
    noun.to_word_case("possessive");
    cout << noun << endl;

    return 0;
}