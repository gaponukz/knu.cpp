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

template<typename TYPE>LinkedList<TYPE>* Tensor<TYPE>::create_ndim_array(int dimension, const int *shape, int dimLevel) {
    if (dimension < 1) {
        return nullptr;

    } else {
        auto *res = new LinkedList<TYPE>[shape[dimLevel]];

        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            res[itr] = LinkedList<TYPE>();

            if (dimension == 1) {
                res[itr].next = nullptr;

            } else {
                res[itr].next = create_ndim_array(dimension-1, shape, dimLevel+1);

            }
        
            res[itr].value = 0;
        }
        return res;
    }
}

template<typename TYPE>LinkedList<TYPE>* Tensor<TYPE>::create_ndim_array(int dimension, const int *shape) {
    return create_ndim_array(dimension, shape, 0);
}

template <typename TYPE>void Tensor<TYPE>::delete_ndim_array(LinkedList<TYPE> *array, int dimension, const int *shape, int dimLevel) {
    if (dimension > 1) {
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            delete_ndim_array(array[itr].next, dimension - 1, shape, dimLevel + 1);
        }
    }

    delete[] array;
}

template <typename TYPE>LinkedList<TYPE>* Tensor<TYPE>::copy_ndim_array(LinkedList<TYPE> *array,int dimension, const int *shape, int dimLevel) {
    if (dimension < 1) {
        return nullptr;
    }

    auto *result = new LinkedList<TYPE>[shape[dimLevel]];

    for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
        LinkedList<TYPE> tmp;
    
        if (dimension > 1) {
            tmp.next = copy_ndim_array(array[itr].next, dimension-1, shape, dimLevel + 1);
            tmp.value = 0;
    
        } else {
            tmp.value = array[itr].value;
            tmp.next = nullptr;
        }
    
        result[itr] = tmp;
    }
    return result;
}

template <typename TYPE>void Tensor<TYPE>::delete_ndim_array(LinkedList<TYPE> *array, int dimension, const int *shape) {
    delete_ndim_array(array, dimension, shape, 0);
}

// Costructors...
template<typename TYPE>Tensor<TYPE>::Tensor(TYPE element):mShape(nullptr),mArray(nullptr) {
    mShape = new int[1];
    mShape[0] = 1;
    mArray = new LinkedList<TYPE>[1];
    mArray[0].next = nullptr;
    mArray[0].value = element;
    number_dim = 1;
}

/**
 * Main constructor, from technical task
 * 
 * @param LinkedList* масив даних тензору
 * @param int dimension: натуральне число – кількість N розмірностей тензору; 
 * @param const int *shape: вказівник на натуральні числа, - це масив з N чисел, величини першоЇ, другої … N-тої розмірності даного тензору
*/

template<typename TYPE>Tensor<TYPE>::Tensor(LinkedList<TYPE> *array, int dimension, const int *shape):mShape(nullptr),mArray(nullptr) {
    number_dim = dimension;
    mShape = new int[dimension];

    for (size_t itr = 0; itr < dimension; ++itr) {
        mShape[itr] = shape[itr];
    }

    mArray = array;
}

template<typename TYPE>Tensor<TYPE>::Tensor(int dimension, const int *shape):mShape(nullptr),mArray(nullptr) {
    number_dim = dimension;
    mShape = new int[dimension];
    
    for (size_t itr = 0; itr < dimension; ++itr) {
        mShape[itr] = shape[itr];
    }
    
    mArray = create_ndim_array(dimension, shape);
}

// Dectructor
template <typename TYPE>Tensor<TYPE>::~Tensor() {
    delete_ndim_array(mArray, number_dim, mShape);
    delete[] mShape;
    number_dim = 0;
}

template<typename TYPE>void Tensor<TYPE>::create_chain(LinkedList<TYPE> *array, int dimLevel, TYPE *resArray, int &startIndex) {
    if (number_dim - dimLevel < 1) {
        return;
    
    } else if (number_dim - dimLevel == 1) {
        for (size_t itr = 0; itr < mShape[dimLevel]; ++itr) {
            resArray[startIndex] = array[itr].value;
            startIndex++;
        }

    } else {
        for (size_t itr = 0; itr < mShape[dimLevel]; ++itr) {
            create_chain(array[itr].next, dimLevel + 1, resArray, startIndex);
        }
    }
}

template<typename TYPE>TYPE* Tensor<TYPE>::chain() {
    int amount = 1;

    for (size_t itr = 0; itr < number_dim; ++itr) {
        amount *= mShape[itr];
    }

    if (number_dim >= 1) {
        TYPE *resArray = new TYPE[amount];
        int startIndex = 0;
        create_chain(mArray, 0, resArray, startIndex);
        return resArray;
    } else {
        TYPE *resArray = nullptr;
        return resArray;
    }
}

template <typename TYPE>void Tensor<TYPE>::fill_array_from_chain(LinkedList<TYPE> *array, int dimLevel, TYPE *_chain, int &startIndex) {
    if (number_dim - dimLevel < 1) {
        return;

    } else if (number_dim - dimLevel == 1) {
        for (size_t itr = 0; itr < mShape[dimLevel]; ++itr) {
            array[itr].value = _chain[startIndex];
            startIndex++;
        }
        return;

    } else {
        for (size_t itr = 0; itr < mShape[dimLevel]; ++itr) {
            fill_array_from_chain(array[itr].next, dimLevel + 1, _chain, startIndex);
        }
        return;
    }
}

/**
 * Reshape tensor
 *
 * @params new dimension and new shape, nothing special 
 */
template<typename TYPE>void Tensor<TYPE>::reshape(int new_dimension, const int *new_shape) {
    int amount1 = 1;
    int amount2 = 1;

    for (size_t itr = 0; itr < number_dim; ++itr) {
        amount1 *= mShape[itr];
    }

    for (size_t itr = 0; itr < new_dimension; ++itr) {
        amount2 *= new_shape[itr];
    }

    if (amount1 != amount2) {
        throw std::length_error("Can not reshape.");
    }

    TYPE *_chain = chain();

    LinkedList<TYPE> *newArray = create_ndim_array(new_dimension, new_shape);
    number_dim = new_dimension;
    mShape = new int[new_dimension];

    for (size_t itr = 0; itr < new_dimension; ++itr) {
        mShape[itr] = new_shape[itr];
    }

    int startIndex = 0;
    fill_array_from_chain(newArray, 0, _chain, startIndex);
    mArray = newArray;
}

// Copy object
template<typename TYPE>Tensor<TYPE>& Tensor<TYPE>::copy() {
    auto *result = new Tensor<TYPE>(number_dim, mShape);
    result -> mArray = copy_ndim_array(mArray, number_dim, mShape, 0);
    return *result;
}

template<typename TYPE>Tensor<TYPE>& Tensor<TYPE>::operator=(const Tensor<TYPE> &other) {
    if (this != &other) {
        if (this -> number_dim != other.number_dim) throw std::invalid_argument("Different dimensions");
        bool success = true;

        for (size_t itr = 0; itr < this -> number_dim; ++itr) {
            if (this -> mShape[itr] != other.mShape[itr]) {
                success = false;
                break;
            }
        }

        if (!success) throw std::invalid_argument("Different shapes");
        copy_values(this->mArray, other.mArray, number_dim, mShape, 0);
    }

    return *this;
}

template<typename TYPE>Tensor<TYPE>& Tensor<TYPE>::operator[](int i) {
    if (i > mShape[0] || i < 0) {
        throw std::out_of_range("Out of range");
   
    } else if (number_dim > 1) {
        auto *new_shape = new int[number_dim - 1];

        for (size_t itr = 0; itr < number_dim - 1; ++itr) {
            new_shape[itr] = mShape[itr+1];
        }
        
        auto *result = new Tensor<TYPE>(mArray[i].next, number_dim - 1, new_shape);
        return *result;

    } else {
        // Tensor<TYPE>();
        auto *tmpArr = &mArray[i];
        auto *tmpShape = new int[1];
        tmpShape[0] = 1;
        auto *res = new Tensor<TYPE>(tmpArr, 1, tmpShape);
        return *res;
    }
}

template<typename TYPE>void Tensor<TYPE>::print() {
    print_ndim_array(std::cout, mArray, number_dim, mShape, 0);
    std::cout << std::endl;
}

template<typename TYPE>void Tensor<TYPE>::write(std::ostream &stream) {
    print_ndim_array(stream, mArray, number_dim, mShape, 0);
    stream << std::endl;
}

template<typename TYPE>void Tensor<TYPE>::print_ndim_array(std::ostream &stream, LinkedList<TYPE> *array, int dimension, const int *shape, int dimLevel) {
    if (dimension == 1) {
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            stream << array[itr].value << ' ';
        }
        stream << std::endl;

    } else {
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            print_ndim_array(stream, array[itr].next, dimension-1, shape, dimLevel+1);
            for (size_t i = 0; i < dimension-2; i++) {
                stream << std::endl;
            }
        }
    }
}

template <typename TYPE>void Tensor<TYPE>::copy_values(LinkedList<TYPE> *array1, LinkedList<TYPE> *array2, int dimension, const int *shape, int dimLevel) {
    if (dimension == 1) {
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            array1[itr].value = array2[itr].value;
        }

    } else {
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            copy_values(array1[itr].next, array2[itr].next, dimension - 1, shape, dimLevel + 1);
        }
    }
}

template <typename TYPE>void Tensor<TYPE>::unary_operation(TYPE (*ptr2Func)(TYPE ,TYPE ), LinkedList<TYPE> *array, TYPE singleElement, LinkedList<TYPE> *resArray, int dimension, const int *shape, int dimLevel) {
    if (dimension == 1) {
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            resArray[itr].value = (*ptr2Func)(array[itr].value, singleElement);
        }

    } else {
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            unary_operation(ptr2Func, array[itr].next, singleElement, resArray[itr].next, dimension-1, shape, dimLevel + 1);
        }
    }
}

template <typename TYPE>void Tensor<TYPE>::binary_operation(TYPE (*ptr2Func)(TYPE , TYPE ), LinkedList<TYPE> *array1, LinkedList<TYPE> *array2, LinkedList<TYPE> *resArray, int dimensional, const int *shape, int dimLevel) {
    if (dimensional == 1) {
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            resArray[itr].value = (*ptr2Func)(array1[itr].value, array2[itr].value);
        }
    } else {
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            binary_operation(ptr2Func, array1[itr].next, array2[itr].next, resArray[itr].next, dimensional-1, shape, dimLevel + 1);
        }
    }
}

static void check_same(int dim1, int dim2, const int *shape1, const int *shape2) {
    if (dim1 != dim2) {
        throw std::invalid_argument("dim1 != dim2");
    }
    
    bool succ = true;
    
    for (size_t itr = 0; itr < dim1; ++itr) {
        if (shape1[itr] != shape2[itr]) {
            succ = false;
            break;
        }   
    }

    if (!succ) {
        throw std::invalid_argument("different shape");
    }
}

template <typename TYPE>Tensor<TYPE>& Tensor<TYPE>::operator+(const Tensor<TYPE> &other) {
    check_same(this->number_dim, other.number_dim, this->mShape, other.mShape);
    auto *result = new Tensor<TYPE>(number_dim, mShape);
    binary_operation(&Tensor<TYPE>::sum, this->mArray, other.mArray, result->mArray, this->number_dim, this->mShape, 0);

    return *result;
}

template<typename TYPE>Tensor<TYPE>& Tensor<TYPE>::operator-(const Tensor<TYPE> &other) {
    check_same(this->number_dim, other.number_dim, this->mShape, other.mShape);
    auto *result = new Tensor<TYPE>(number_dim, mShape);
    binary_operation(&Tensor<TYPE>::sub, this->mArray, other.mArray, result->mArray, this->number_dim, this->mShape, 0);

    return *result;
}

template<typename TYPE>Tensor<TYPE>& Tensor<TYPE>::operator*(const Tensor<TYPE> &other) {
    check_same(this->number_dim, other.number_dim, this->mShape, other.mShape);
    auto *result = new Tensor<TYPE>(number_dim, mShape);
    binary_operation(&Tensor<TYPE>::mul, this->mArray, other.mArray, result->mArray, this->number_dim, this->mShape, 0);

    return *result;
}

template<typename TYPE>Tensor<TYPE>& Tensor<TYPE>::operator/(const Tensor<TYPE> &other) {
    check_same(this->number_dim, other.number_dim, this->mShape, other.mShape);
    auto *result = new Tensor<TYPE>(number_dim, mShape);
    binary_operation(&Tensor<TYPE>::div, this->mArray, other.mArray, result->mArray, this->number_dim, this->mShape, 0);
    
    return *result;
}

template<typename TYPE>Tensor<TYPE>& Tensor<TYPE>::operator+(TYPE singleElement) {
    auto *result = new Tensor<TYPE>(number_dim, mShape);
    unary_operation(Tensor<TYPE>::sum, this->mArray, singleElement, result->mArray, this->number_dim, this->mShape, 0);
    
    return *result;
}

template<typename TYPE>Tensor<TYPE>& Tensor<TYPE>::operator-(TYPE singleElement) {
    auto *result = new Tensor<TYPE>(number_dim, mShape);
    unary_operation(Tensor<TYPE>::sub, this->mArray, singleElement, result->mArray, this->number_dim, this->mShape, 0);
    
    return *result;
}

template<typename TYPE>Tensor<TYPE>& Tensor<TYPE>::operator*(TYPE singleElement) {
    auto *result = new Tensor<TYPE>(number_dim, mShape);
    unary_operation(Tensor<TYPE>::mul, this->mArray, singleElement, result->mArray, this->number_dim, this->mShape, 0);
    
    return *result;
}

template<typename TYPE>Tensor<TYPE>& Tensor<TYPE>::operator/(TYPE singleElement) {
    auto *result = new Tensor<TYPE>(number_dim, mShape);
    unary_operation(Tensor<TYPE>::div, this->mArray, singleElement, result->mArray, this->number_dim, this->mShape, 0);
    
    return *result;
}

template <typename TYPE>bool Tensor<TYPE>::operator==(const Tensor<TYPE> &other) {
    if (this -> number_dim != other.number_dim) return false;

    for (size_t itr = 0; itr < number_dim; ++itr) {
        if (this->mShape[itr] != other.mShape[itr]) {
            return false;
        }
    }

    return is_equal(this->mArray, other.mArray, number_dim, mShape, 0);
}

template <typename TYPE>bool Tensor<TYPE>::is_equal(LinkedList<TYPE> *array1, LinkedList<TYPE> *array2, int dimensional, const int *shape, int dimLevel) {
    if (dimensional == 1) {
        return array1[0].value == array2[0].value;
    } else {
        bool success = true;
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            success &= is_equal(array1[itr].next, array2[itr].next, dimensional-1, shape, dimLevel+1);
            if (!success) break;

        }
    return success;
    }
}

template <typename TYPE>void Tensor<TYPE>::to_file(const std::string &filename) {
    std::ofstream fs(filename, std::ios::out | std::ios::binary | std::ios::app);
    int* _shape = shape();
    TYPE* _chain = chain();

    int amount = 1;

    for (size_t itr = 0; itr < number_dim; ++itr) {
        amount *= mShape[itr];
    }

    fs.write(reinterpret_cast<const char *>(&number_dim), sizeof(number_dim));
    fs.write(reinterpret_cast<const char *>(&_chain[0]), amount*sizeof(TYPE));
    fs.write(reinterpret_cast<const char *>(&_shape[0]), number_dim*sizeof(int));
    fs.close();
}

template <typename TYPE>Tensor<TYPE> from_file(const std::string &filename) {
    ifstream fs(filename, ios::in | ios::binary | std::ios::app);
    int _number_dim;
    int* _shape;
    TYPE* _chain;
    int amount = 1;
    int startIndex = 0;

    fs.read((char *)(&_number_dim), sizeof(_number_dim));
    fs.read((char *)(&_shape[0]), _number_dim*sizeof(int));

    for (size_t itr = 0; itr < _number_dim; ++itr) {
        amount *= _shape[itr];
    }

    fs.read((char *)(&_chain[0]), amount*sizeof(TYPE));
    fs.close();

    Tensor<TYPE> _new(_number_dim, _shape);
    LinkedList<TYPE>* newArray = _new.create_ndim_array(_number_dim, _shape);

    _new.fill_array_from_chain(newArray, _number_dim, _chain, startIndex);
    
    return _new;
};
