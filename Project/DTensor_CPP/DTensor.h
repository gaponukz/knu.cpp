#include <iostream>
#include <fstream>
#include <string>

using namespace std;
// Abstract data double linked list
struct LinkedList{
    double value;
    LinkedList *next;
};

// Main class
class Tensor {
public:
    Tensor();
    ~Tensor();
    Tensor(int dimension, const int *shape);

    explicit Tensor(double element);
    void reshape(int new_dimension, const int *new_shape);

    int dimension() { return number_dim; };
    int *shape() {
        auto result_shape = new int[number_dim];

        for (size_t itr = 0; itr < number_dim; ++itr) {
            result_shape[itr] = mShape[itr];
        }
        return result_shape;
    };

    double* chain();
    void fill_array_from_chain(LinkedList *array, int dimLevel, double *_chain, int &startIndex);
    LinkedList *create_ndim_array(int dimension, const int *shape, int dimLevel);
    LinkedList *create_ndim_array(int dimension, const int *shape);

    Tensor &operator=(const Tensor &other);
    Tensor &operator[](int i);
    Tensor &operator+(const Tensor &other);
    Tensor &operator-(const Tensor &other);
    Tensor &operator*(const Tensor &other);
    Tensor &operator/(const Tensor &other);
    Tensor &operator+(double singleElement);
    Tensor &operator-(double singleElement);
    Tensor &operator*(double singleElement);
    Tensor &operator/(double singleElement);
    bool operator==(const Tensor &other);
    
    Tensor &copy();

    void print();
    void write(std::ostream &stream);
    void to_file(const std::string &filename);
    void set_marray(LinkedList * new_marray);

    static double sum(double x, double y) { return x + y; };
    static double sub(double x, double y) { return x - y; };
    static double mul(double x, double y) { return x * y; };
    static double div(double x, double y) {
        if (y == 0) throw std::invalid_argument("Divide by zero");
        return x / y;
    };

private:

    int number_dim = 0;
    LinkedList *mArray;
    int *mShape;

    Tensor(LinkedList *array, int dimension, const int *shape);
    LinkedList *copy_ndim_array(LinkedList *array,int dimension, const int *shape,  int dimLevel);

    void delete_ndim_array(LinkedList *array, int dimension, const int *shape, int dimLevel);
    void delete_ndim_array(LinkedList *array, int dimension, const int *shape);
    void create_chain(LinkedList *array, int dimLevel, double *resArray, int &startIndex);

    void print_ndim_array(std::ostream &stream, LinkedList *array, int dimension, const int *shape, int dimLevel);
    void copy_values(LinkedList *array1, LinkedList *array2, int dimension, const int *shape, int dimLevel);
    void unary_operation(double (*ptr2Func)(double , double ), LinkedList *array, double singleElement, LinkedList *resArray, int dimension, const int *shape, int dimLevel);
    void binary_operation(double (*ptr2Func)(double , double ), LinkedList *array1, LinkedList *array2, LinkedList *resArray, int dimensional, const int *shape, int dimLevel);
    bool is_equal(LinkedList *array1, LinkedList *array2, int dimensional, const int *shape, int dimLevel);
};

Tensor from_file(const std::string &filename);
