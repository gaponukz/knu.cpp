LinkedList* create_ndim_array(int dimension, const int *shape, int dimLevel) {
    LinkedList *res = (LinkedList*)malloc(shape[dimLevel] * sizeof(LinkedList));

    for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
        LinkedList item;
        res[itr] = item;

        if (dimension == 1) {
            res[itr].next = NULL;

        } else {
            res[itr].next = create_ndim_array(dimension-1, shape, dimLevel+1);

        }
    
        res[itr].value = 0;
    }
    return res;

}

void delete_ndim_array(LinkedList* array, int dimension, const int *shape, int dimLevel) {
    if (dimension > 1) {
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            delete_ndim_array(array[itr].next, dimension - 1, shape, dimLevel + 1);
        }
    }

    free(array);
}

LinkedList* copy_ndim_array(LinkedList *array, int dimension, const int *shape, int dimLevel) {
    LinkedList *result = (LinkedList*)malloc(shape[dimLevel] * sizeof(LinkedList));

    for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
        LinkedList tmp;
    
        if (dimension > 1) {
            tmp.next = copy_ndim_array(array[itr].next, dimension-1, shape, dimLevel + 1);
            tmp.value = 0;
    
        } else {
            tmp.value = array[itr].value;
            tmp.next = NULL;
        }
    
        result[itr] = tmp;
    }
    return result;
}

/**
 * Main constructor, from technical task
 * 
 * @param LinkedList* масив даних тензору
 * @param int dimension: натуральне число – кількість N розмірностей тензору; 
 * @param const int *shape: вказівник на натуральні числа, - це масив з N чисел, величини першоЇ, другої … N-тої розмірності даного тензору
*/
Tensor TensorInitFull(LinkedList* array, int dimension, const int *shape) {
    Tensor tensor;
    tensor.number_dim = dimension;
    tensor.mShape = (int*)malloc(dimension * sizeof(int));

    for (size_t itr = 0; itr < dimension; ++itr) {
        tensor.mShape[itr] = shape[itr];
    }

    tensor.mArray = array;

    return tensor;
}

Tensor TensorInitZero(int dimension, const int *shape) {
    Tensor tensor;
    tensor.number_dim = dimension;
    tensor.mShape = (int*)malloc(dimension * sizeof(int));
    
    for (size_t itr = 0; itr < dimension; ++itr) {
        tensor.mShape[itr] = shape[itr];
    }
    
    tensor.mArray = create_ndim_array(dimension, shape, 0);

    return tensor;
}

Tensor TensorInitOne(double element) {
    Tensor tensor;
    tensor.mShape = (int*)malloc(sizeof(int));
    tensor.mShape[0] = 1;
    tensor.mArray = (LinkedList*)malloc(sizeof(LinkedList));
    tensor.mArray[0].next = NULL;
    tensor.mArray[0].value = element;
    tensor.number_dim = 1;

    return tensor;
}

Tensor at(Tensor tensor, int i) {
    if (tensor.number_dim > 1) {
        int *new_shape = (int*)malloc((tensor.number_dim-1)*sizeof(int));

        for (size_t itr = 0; itr < tensor.number_dim - 1; ++itr) {
            new_shape[itr] = tensor.mShape[itr+1];
        }
        
        Tensor result = TensorInit(tensor.mArray[i].next, tensor.number_dim - 1, new_shape);
        return result;

    } else {
        int* tmpShape = (int*)malloc(sizeof(int));
        tmpShape[0] = 1;
        Tensor res = TensorInit(&tensor.mArray[i], 1, tmpShape);
        return res;
    }
}

void create_chain(Tensor tensor, LinkedList* array, int dimLevel, double *resArray, int startIndex) {
    if (tensor.number_dim - dimLevel < 1) {
        return;
    
    } else if (tensor.number_dim - dimLevel == 1) {
        for (size_t itr = 0; itr < tensor.mShape[dimLevel]; ++itr) {
            resArray[startIndex] = array[itr].value;
            startIndex++;
        }

    } else {
        for (size_t itr = 0; itr < tensor.mShape[dimLevel]; ++itr) {
            create_chain(tensor, array[itr].next, dimLevel + 1, resArray, startIndex);
        }
    }
}

double* chain(Tensor tensor) {
    int amount = 1;

    for (size_t itr = 0; itr < tensor.number_dim; ++itr) {
        amount *= tensor.mShape[itr];
    }

    double* resArray = (double*)malloc(amount * sizeof(double));
    int startIndex = 0;
    create_chain(tensor, tensor.mArray, 0, resArray, startIndex);
    return resArray;

}

void fill_array_from_chain(Tensor tensor, LinkedList* array, int dimLevel, double *_chain, int startIndex) {
    if (tensor.number_dim - dimLevel < 1) {
        return;

    } else if (tensor.number_dim - dimLevel == 1) {
        for (size_t itr = 0; itr < tensor.mShape[dimLevel]; ++itr) {
            array[itr].value = _chain[startIndex];
            startIndex++;
        }
        return;

    } else {
        for (size_t itr = 0; itr < tensor.mShape[dimLevel]; ++itr) {
            fill_array_from_chain(tensor, array[itr].next, dimLevel + 1, _chain, startIndex);
        }
        return;
    }
}

/**
 * Reshape tensor
 *
 * @params new dimension and new shape, nothing special 
 */
Tensor reshape(Tensor tensor, int new_dimension, const int *new_shape) {
    int amount1 = 1;
    int amount2 = 1;

    for (size_t itr = 0; itr < tensor.number_dim; ++itr) {
        amount1 *= tensor.mShape[itr];
    }

    for (size_t itr = 0; itr < new_dimension; ++itr) {
        amount2 *= new_shape[itr];
    }

    double *_chain = chain(tensor);

    LinkedList* newArray = create_ndim_array(new_dimension, new_shape, 0);
    tensor.number_dim = new_dimension;
    tensor.mShape = (int*)malloc(new_dimension * sizeof(int));

    for (size_t itr = 0; itr < new_dimension; ++itr) {
        tensor.mShape[itr] = new_shape[itr];
    }

    int startIndex = 0;
    fill_array_from_chain(tensor, newArray, 0, _chain, startIndex);
    tensor.mArray = newArray;

    return tensor;
}

// Copy object
Tensor copy(Tensor tensor) {
    Tensor result = TensorInit(tensor.number_dim, tensor.mShape);

    result.mArray = copy_ndim_array(tensor.mArray, tensor.number_dim, tensor.mShape, 0);
    return result;
}

void print_ndim_array(LinkedList* array, int dimension, int *shape, int dimLevel) {
    if (dimension == 1) {
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            printf("%lf ", array[itr].value);
        }
        printf("\n");

    } else {
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            print_ndim_array(array[itr].next, dimension-1, shape, dimLevel+1);
            for (size_t i = 0; i < dimension-2; i++) {
                printf("\n");
            }
        }
    }
}

void print(Tensor tensor) {
    print_ndim_array(tensor.mArray, tensor.number_dim, tensor.mShape, 0);
    printf("\n");
}

void unary_operation(Tensor tensor, double (*ptr2Func)(double, double), LinkedList* array, double singleElement, LinkedList* resArray, int dimension, const int *shape, int dimLevel) {
    if (dimension == 1) {
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            resArray[itr].value = (*ptr2Func)(array[itr].value, singleElement);
        }

    } else {
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            unary_operation(tensor, ptr2Func, array[itr].next, singleElement, resArray[itr].next, dimension-1, shape, dimLevel + 1);
        }
    }
}

void binary_operation(Tensor tensor, double (*ptr2Func)(double, double ), LinkedList* array1, LinkedList* array2, LinkedList* resArray, int dimensional, const int *shape, int dimLevel) {
    if (dimensional == 1) {
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            resArray[itr].value = (*ptr2Func)(array1[itr].value, array2[itr].value);
        }
    } else {
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            binary_operation(tensor, ptr2Func, array1[itr].next, array2[itr].next, resArray[itr].next, dimensional-1, shape, dimLevel + 1);
        }
    }
}

int check_same(int dim1, int dim2, const int *shape1, const int *shape2) {
    int succ = 1;
    
    for (size_t itr = 0; itr < dim1; ++itr) {
        if (shape1[itr] != shape2[itr]) {
            succ = 0;
            break;
        }   
    }

    return succ;
}

int is_equal(LinkedList* array1, LinkedList* array2, int dimensional, const int *shape, int dimLevel) {
    if (dimensional == 1) {
        return array1[0].value == array2[0].value;

    } else {
        int success = 1;
        for (size_t itr = 0; itr < shape[dimLevel]; ++itr) {
            success &= is_equal(array1[itr].next, array2[itr].next, dimensional-1, shape, dimLevel+1);
            if (!success) break;

        }
    return success;
    }
}

void set_marray(Tensor tensor, LinkedList* new_marray) {
    tensor.mArray = new_marray;
}

void to_file(Tensor tensor, const char filename[]) {
    // TODO: logic
}

Tensor from_file(const char filename[]) {
    Tensor _new = TensorInit(0);
    // TODO: logic
    return _new;
};
