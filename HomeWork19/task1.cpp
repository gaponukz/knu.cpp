#include <iostream>
#include <cmath>
#include <list>

using namespace std;

struct Numbers {
    list<double> numbers;

    void add(double x) {
        numbers.push_back(x);
    };

    void remove(double x) {
        numbers.remove(x);
    }

    double get(double x) {
        double result = -INFINITY;
        list<double>::iterator it = numbers.begin();

        while (it != numbers.end()) {
            if (fabs(*it - x) < fabs(*it - result)) {
                result = *it;
            }
            it++;
        }

        return result;
    }
};


int main(int argc, char** argv) {
    Numbers data;

    data.add(1);
    data.add(0.7);
    data.add(0.5);
    data.add(0.2);
    data.add(0);

    cout << data.get(0.3) << endl;

    return 0;
}
