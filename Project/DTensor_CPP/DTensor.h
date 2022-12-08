#include <iostream>
#include <fstream>
#include <string>

using namespace std;
// Abstract data type linked list
template<typename TYPE>struct LinkedList{
    TYPE value;
    LinkedList *next;
};

// Main class
template<typename TYPE>class Tensor {
public:
    Tensor();
    ~Tensor();
    Tensor(int dimension, const int *shape);

    explicit Tensor(TYPE element);
    void reshape(int new_dimension, const int *new_shape);

    int dimension() { return number_dim; };
    int *shape() {
        auto result_shape = new int[number_dim];

        for (size_t itr = 0; itr < number_dim; ++itr) {
            result_shape[itr] = mShape[itr];
        }
        return result_shape;
    };

    TYPE* chain();
    void fill_array_from_chain(LinkedList<TYPE> *array, int dimLevel, TYPE *_chain, int &startIndex);
    LinkedList<TYPE> *create_ndim_array(int dimension, const int *shape, int dimLevel);
    LinkedList<TYPE> *create_ndim_array(int dimension, const int *shape);

    Tensor<TYPE> &operator=(const Tensor<TYPE> &other);
    Tensor<TYPE> &operator[](int i);
    Tensor<TYPE> &operator+(const Tensor<TYPE> &other);
    Tensor<TYPE> &operator-(const Tensor<TYPE> &other);
    Tensor<TYPE> &operator*(const Tensor<TYPE> &other);
    Tensor<TYPE> &operator/(const Tensor<TYPE> &other);
    Tensor<TYPE> &operator+(TYPE singleElement);
    Tensor<TYPE> &operator-(TYPE singleElement);
    Tensor<TYPE> &operator*(TYPE singleElement);
    Tensor<TYPE> &operator/(TYPE singleElement);
    bool operator==(const Tensor<TYPE> &other);
    
    Tensor<TYPE> &copy();

    void print();
    void write(std::ostream &stream);
    void to_file(const std::string &filename);

    static TYPE sum(TYPE x, TYPE y) { return x + y; };
    static TYPE sub(TYPE x, TYPE y) { return x - y; };
    static TYPE mul(TYPE x, TYPE y) { return x * y; };
    static TYPE div(TYPE x, TYPE y) {
        if (y == 0) throw std::invalid_argument("Divide by zero");
        return x / y;
    };

private:

    int number_dim = 0;
    LinkedList<TYPE> *mArray;
    int *mShape;

    Tensor(LinkedList<TYPE> *array, int dimension, const int *shape);
    LinkedList<TYPE> *copy_ndim_array(LinkedList<TYPE> *array,int dimension, const int *shape,  int dimLevel);

    void delete_ndim_array(LinkedList<TYPE> *array, int dimension, const int *shape, int dimLevel);
    void delete_ndim_array(LinkedList<TYPE> *array, int dimension, const int *shape);
    void create_chain(LinkedList<TYPE> *array, int dimLevel, TYPE *resArray, int &startIndex);

    void print_ndim_array(std::ostream &stream, LinkedList<TYPE> *array, int dimension, const int *shape, int dimLevel);
    void copy_values(LinkedList<TYPE> *array1, LinkedList<TYPE> *array2, int dimension, const int *shape, int dimLevel);
    void unary_operation(TYPE (*ptr2Func)(TYPE , TYPE ), LinkedList<TYPE> *array, TYPE singleElement, LinkedList<TYPE> *resArray, int dimension, const int *shape, int dimLevel);
    void binary_operation(TYPE (*ptr2Func)(TYPE , TYPE ), LinkedList<TYPE> *array1, LinkedList<TYPE> *array2, LinkedList<TYPE> *resArray, int dimensional, const int *shape, int dimLevel);
    bool is_equal(LinkedList<TYPE> *array1, LinkedList<TYPE> *array2, int dimensional, const int *shape, int dimLevel);
};

template <typename TYPE>Tensor<TYPE> from_file(const std::string &filename);
