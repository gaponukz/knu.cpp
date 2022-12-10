#include <iostream>
#include <cassert>
#include <fstream>
#include "DTensor.h"
#include "DTensor.cpp"

using namespace std;

int main(int argc, char **argv) {
    fstream file("DTensor_test.txt", ios::out);

    if (!file.is_open()){
        cout << "Could not open the file" << endl;

        return 1;
    }
    const short int dim = 2;
    const short int n = 2;
    const short int m = 3;

    int shape[dim] = {n, m};
    Tensor test1(dim, shape);

    assert(test1[0][0] == Tensor(0));

    int x = 0;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            test1[i][j] = Tensor(x);
            x++;
        }
    }
    assert(test1[0][0] == Tensor(0));

    test1.to_file("test1.dte");

    Tensor test_from_file = from_file("test1.dte");
    // test_from_file.print();

    assert(test_from_file == test1);

    cout << "test1:" << endl;
    test1.print();

    file << "test1:" << endl;
    test1.write(file);

    auto *new_shape = new int[2];
    new_shape[0] = 3;
    new_shape[1] = 2;

    auto test2 = test1.copy();

    assert(test1 == test2);

    test2.reshape(2, new_shape);
    assert(test2[0][0] == Tensor(0));

    cout << "test1 after reshape:" << endl;
    test2.print();

    file << "test1 after reshape:" << endl;
    test2.write(file);

    auto test3 = (((test1.copy() + 3) - 1) * 2) / 4 + 1;

    cout << "test3 = (test1 + 3 - 1) * 2 / 4  + 1" << endl;
    test3.print();

    file << "test3 = (test1 + 3 - 1) * 2 / 4  + 1" << endl;
    test3.write(file);

    cout << "(test1 + test3 - test1 * test3) / test3" << endl;
    ((test1 + test3 - test1*test3)/test3).print();

    file << "(test1 + test3 - test1 * test3) / test3" << endl;
    ((test1 + test3 - test1*test3)/test3).write(file);

    return 0;
}