#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

class Person {

    string name;
    unsigned byear;

public:

    Person(const string& _name, unsigned _byear): name(_name), byear(_byear) {}

    string get_name() const {return name;}
    void set_name(const string& name) {this->name = name;}
    unsigned get_byear() const {return byear;}
    void set_byear(unsigned byear) {this->byear = byear;}

    virtual void input(istream& inp = cin) {
        inp >> name >> byear;
    }

    virtual void print(ostream& out = cout) const {
        out << name << ' ' << byear;
    }

    friend ostream& operator<<(ostream& out, const Person& p) {
        p.print(out);
        return out;
    }

    friend istream& operator>>(istream& inp, Person& p) {
        p.input(inp);
        return inp;
    }
};

class Student : public Person {
    double rate100;
    uint32_t rate5;

    public:
    Student(
        const string& _name = "",
        unsigned _byear = 0,
        const double& _rate100 = 0,
        const uint32_t& _rate5 = 0
    ):
        Person(_name, _byear), rate100(_rate100), rate5(_rate5) {}

    void set_rating100(const double& rate) {
        this->rate100 = rate;
    }

    double get_rating100() {
        return this->rate100;
    }
    void set_rating5(const uint32_t& rate) {
        this->rate5 = rate;
    }

    uint32_t get_rating5() {
        return this->rate5;
    }
};

int main(int argc, char** argv) {
    Student st1("Adam", 2003, 83, 4);
    Student st2("Max", 2003, 74, 3);
    Student st3("Igor", 2003, 98, 5);

    Student students[3] = {st1, st2, st3};

    // old system
    for (size_t i = 0; i < 3; i++) {
        if (students[i].get_rating5() >= 4) {
            cout << students[i].get_name() << " will have money" << endl;
        }
    }
    // new system
    sort(students, students+3, [](Student a, Student b) {return (a.get_rating100() > b.get_rating100());});

    for (size_t i = 0; i < (uint32_t)(3 * 0.4); i++) {
        cout << students[i].get_name() << " will have money" << endl;
    }

    return 0;
}
