LinkedList* Tensor::create_ndim_array(int dimension, const int *shape, int dimLevel) {
    if (dimension < 1) {
        return nullptr;

    } else {
        auto *res = new LinkedList[shape[dimLevel]];

        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            res[itr] = LinkedList();

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

LinkedList* Tensor::create_ndim_array(int dimension, const int *shape) {
    return create_ndim_array(dimension, shape, 0);
}

void Tensor::delete_ndim_array(LinkedList *array, int dimension, const int *shape, int dimLevel) {
    if (dimension > 1) {
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            delete_ndim_array(array[itr].next, dimension - 1, shape, dimLevel + 1);
        }
    }

    delete[] array;
}

LinkedList* Tensor::copy_ndim_array(LinkedList *array,int dimension, const int *shape, int dimLevel) {
    if (dimension < 1) {
        return nullptr;
    }

    auto *result = new LinkedList[shape[dimLevel]];

    for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
        LinkedList tmp;
    
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

void Tensor::delete_ndim_array(LinkedList *array, int dimension, const int *shape) {
    delete_ndim_array(array, dimension, shape, 0);
}

// Costructors...
Tensor::Tensor(double element):mShape(nullptr),mArray(nullptr) {
    mShape = new int[1];
    mShape[0] = 1;
    mArray = new LinkedList[1];
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

Tensor::Tensor(LinkedList *array, int dimension, const int *shape):mShape(nullptr),mArray(nullptr) {
    number_dim = dimension;
    mShape = new int[dimension];

    for (size_t itr = 0; itr < dimension; ++itr) {
        mShape[itr] = shape[itr];
    }

    mArray = array;
}

Tensor::Tensor(int dimension, const int *shape):mShape(nullptr),mArray(nullptr) {
    number_dim = dimension;
    mShape = new int[dimension];
    
    for (size_t itr = 0; itr < dimension; ++itr) {
        mShape[itr] = shape[itr];
    }
    
    mArray = create_ndim_array(dimension, shape);
}

// Dectructor
Tensor::~Tensor() {
    delete_ndim_array(mArray, number_dim, mShape);
    delete[] mShape;
    number_dim = 0;
}

void Tensor::create_chain(LinkedList *array, int dimLevel, double *resArray, int &startIndex) {
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

double* Tensor::chain() {
    int amount = 1;

    for (size_t itr = 0; itr < number_dim; ++itr) {
        amount *= mShape[itr];
    }

    if (number_dim >= 1) {
        double *resArray = new double[amount];
        int startIndex = 0;
        create_chain(mArray, 0, resArray, startIndex);
        return resArray;
    } else {
        double *resArray = nullptr;
        return resArray;
    }
}

void Tensor::fill_array_from_chain(LinkedList *array, int dimLevel, double *_chain, int &startIndex) {
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
void Tensor::reshape(int new_dimension, const int *new_shape) {
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

    double *_chain = chain();

    LinkedList *newArray = create_ndim_array(new_dimension, new_shape);
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
Tensor& Tensor::copy() {
    auto *result = new Tensor(number_dim, mShape);
    result -> mArray = copy_ndim_array(mArray, number_dim, mShape, 0);
    return *result;
}

Tensor& Tensor::operator=(const Tensor &other) {
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

Tensor& Tensor::operator[](int i) {
    if (i > mShape[0] || i < 0) {
        throw std::out_of_range("Out of range");
   
    } else if (number_dim > 1) {
        auto *new_shape = new int[number_dim - 1];

        for (size_t itr = 0; itr < number_dim - 1; ++itr) {
            new_shape[itr] = mShape[itr+1];
        }
        
        auto *result = new Tensor(mArray[i].next, number_dim - 1, new_shape);
        return *result;

    } else {
        // Tensor();
        auto *tmpArr = &mArray[i];
        auto *tmpShape = new int[1];
        tmpShape[0] = 1;
        auto *res = new Tensor(tmpArr, 1, tmpShape);
        return *res;
    }
}

void Tensor::print() {
    print_ndim_array(std::cout, mArray, number_dim, mShape, 0);
    std::cout << std::endl;
}

void Tensor::write(std::ostream &stream) {
    print_ndim_array(stream, mArray, number_dim, mShape, 0);
    stream << std::endl;
}

void Tensor::print_ndim_array(std::ostream &stream, LinkedList *array, int dimension, const int *shape, int dimLevel) {
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

void Tensor::copy_values(LinkedList *array1, LinkedList *array2, int dimension, const int *shape, int dimLevel) {
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

void Tensor::unary_operation(double (*ptr2Func)(double ,double ), LinkedList *array, double singleElement, LinkedList *resArray, int dimension, const int *shape, int dimLevel) {
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

void Tensor::binary_operation(double (*ptr2Func)(double , double ), LinkedList *array1, LinkedList *array2, LinkedList *resArray, int dimensional, const int *shape, int dimLevel) {
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

Tensor& Tensor::operator+(const Tensor &other) {
    check_same(this->number_dim, other.number_dim, this->mShape, other.mShape);
    auto *result = new Tensor(number_dim, mShape);
    binary_operation(&Tensor::sum, this->mArray, other.mArray, result->mArray, this->number_dim, this->mShape, 0);

    return *result;
}

Tensor& Tensor::operator-(const Tensor &other) {
    check_same(this->number_dim, other.number_dim, this->mShape, other.mShape);
    auto *result = new Tensor(number_dim, mShape);
    binary_operation(&Tensor::sub, this->mArray, other.mArray, result->mArray, this->number_dim, this->mShape, 0);

    return *result;
}

Tensor& Tensor::operator*(const Tensor &other) {
    check_same(this->number_dim, other.number_dim, this->mShape, other.mShape);
    auto *result = new Tensor(number_dim, mShape);
    binary_operation(&Tensor::mul, this->mArray, other.mArray, result->mArray, this->number_dim, this->mShape, 0);

    return *result;
}

Tensor& Tensor::operator/(const Tensor &other) {
    check_same(this->number_dim, other.number_dim, this->mShape, other.mShape);
    auto *result = new Tensor(number_dim, mShape);
    binary_operation(&Tensor::div, this->mArray, other.mArray, result->mArray, this->number_dim, this->mShape, 0);
    
    return *result;
}

Tensor& Tensor::operator+(double singleElement) {
    auto *result = new Tensor(number_dim, mShape);
    unary_operation(Tensor::sum, this->mArray, singleElement, result->mArray, this->number_dim, this->mShape, 0);
    
    return *result;
}

Tensor& Tensor::operator-(double singleElement) {
    auto *result = new Tensor(number_dim, mShape);
    unary_operation(Tensor::sub, this->mArray, singleElement, result->mArray, this->number_dim, this->mShape, 0);
    
    return *result;
}

Tensor& Tensor::operator*(double singleElement) {
    auto *result = new Tensor(number_dim, mShape);
    unary_operation(Tensor::mul, this->mArray, singleElement, result->mArray, this->number_dim, this->mShape, 0);
    
    return *result;
}

Tensor& Tensor::operator/(double singleElement) {
    auto *result = new Tensor(number_dim, mShape);
    unary_operation(Tensor::div, this->mArray, singleElement, result->mArray, this->number_dim, this->mShape, 0);
    
    return *result;
}

bool Tensor::operator==(const Tensor &other) {
    if (this -> number_dim != other.number_dim) return false;

    for (size_t itr = 0; itr < number_dim; ++itr) {
        if (this->mShape[itr] != other.mShape[itr]) {
            return false;
        }
    }

    return is_equal(this->mArray, other.mArray, number_dim, mShape, 0);
}

bool Tensor::is_equal(LinkedList *array1, LinkedList *array2, int dimensional, const int *shape, int dimLevel) {
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

void Tensor::set_marray(LinkedList* new_marray) {
    mArray = new_marray;
}

void Tensor::to_file(const std::string &filename) {
    std::ofstream fs(filename, ios::out | ios::binary);
    int* _shape = shape();
    double* _chain = chain();

    int amount = 1;

    for (size_t itr = 0; itr < number_dim; ++itr) {
        amount *= mShape[itr];
    }

    fs.write(reinterpret_cast<const char *>(&number_dim), sizeof(int));
    fs.write(reinterpret_cast<const char *>(&_shape), number_dim*sizeof(int));
    fs.write(reinterpret_cast<const char *>(&_chain), amount*sizeof(double));
    fs.close();
}

Tensor from_file(const std::string &filename) {
    ifstream fs(filename, ios::in | ios::binary);
    int _number_dim;
    int amount = 1;
    int startIndex = 0;

    fs.read((char *)(&_number_dim), sizeof(_number_dim));
    const int *_shape = new int(_number_dim);

    fs.read((char *)(&_shape), sizeof(_shape));
    
    for (size_t itr = 0; itr < _number_dim; ++itr) {
        amount *= _shape[itr];
    }

    double* _chain = new double(amount);
    fs.read((char *)(&_chain), sizeof(_chain));
    fs.close();

    Tensor _new(_number_dim, _shape);
    LinkedList* newArray = _new.create_ndim_array(_number_dim, _shape);

    _new.fill_array_from_chain(newArray, 0, _chain, startIndex);
    _new.set_marray(newArray);

    return _new;
};
