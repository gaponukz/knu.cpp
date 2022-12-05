#include "DTensor.h"
#include "stdio.h"

int main(int argc, char **argv) {
    const short int dim = 2;
    const short int n = 2;
    const short int m = 3;

    int shape[2] = {2, 3};
    int values[6] = {0, 1, 2, 3, 4, 5};
    Tensor test1 = TensorInitZero(dim, shape);

    print(test1);
    return 0;
}