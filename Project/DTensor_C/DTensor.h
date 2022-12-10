#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define TENSOR_INIT_1_ARGS(x) TensorInitOne(x)
#define TENSOR_INIT_2_ARGS(x, y) TensorInitZero(x, y)
#define TENSOR_INIT_3_ARGS(x, y, z) TensorInitFull(x, y, z)

#define GET_4TH_ARG(arg1, arg2, arg3, arg4, ...) arg4
#define TENSOR_INIT_MACRO_CHOOSER(...) GET_4TH_ARG(__VA_ARGS__, TENSOR_INIT_3_ARGS, TENSOR_INIT_2_ARGS, TENSOR_INIT_1_ARGS, )

#define TensorInit(...) TENSOR_INIT_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

typedef struct LinkedList LinkedList;
struct LinkedList{
    double value;
    LinkedList *next; 
};

typedef struct Tensor Tensor;
struct Tensor {
    int number_dim;
    LinkedList *mArray;
    int *mShape;
};

LinkedList* create_ndim_array(int dimension, const int *shape, int dimLevel);

void delete_ndim_array(LinkedList* array, int dimension, const int *shape, int dimLevel);

LinkedList* copy_ndim_array(LinkedList *array, int dimension, const int *shape, int dimLevel);

/**
 * Main constructor, from technical task
 * 
 * @param LinkedList* масив даних тензору
 * @param int dimension: натуральне число – кількість N розмірностей тензору; 
 * @param const int *shape: вказівник на натуральні числа, - це масив з N чисел, величини першоЇ, другої … N-тої розмірності даного тензору
*/
Tensor TensorInitFull(LinkedList* array, int dimension, const int *shape);

Tensor TensorInitZero(int dimension, const int *shape);

Tensor TensorInitOne(double element);

Tensor at(Tensor tensor, int i);

void create_chain(Tensor tensor, LinkedList* array, int dimLevel, double *resArray, int startIndex);

double* chain(Tensor tensor);

void fill_array_from_chain(Tensor tensor, LinkedList* array, int dimLevel, double *_chain, int startIndex);

/**
 * Reshape tensor
 *
 * @params new dimension and new shape, nothing special 
 */
Tensor reshape(Tensor tensor, int new_dimension, const int *new_shape);

// Copy object
Tensor copy(Tensor tensor);

void print_ndim_array(LinkedList* array, int dimension, int *shape, int dimLevel);

void print(Tensor tensor);

void unary_operation(Tensor tensor, double (*ptr2Func)(double, double), LinkedList* array, double singleElement, LinkedList* resArray, int dimension, const int *shape, int dimLevel);

void binary_operation(Tensor tensor, double (*ptr2Func)(double, double ), LinkedList* array1, LinkedList* array2, LinkedList* resArray, int dimensional, const int *shape, int dimLevel);

int check_same(int dim1, int dim2, const int *shape1, const int *shape2);

int is_equal(LinkedList* array1, LinkedList* array2, int dimensional, const int *shape, int dimLevel);

void set_marray(Tensor tensor, LinkedList* new_marray);

void to_file(Tensor tensor, const char filename[]);

Tensor from_file(const char filename[]);
