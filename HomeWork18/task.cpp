#include <iostream>
#include <random>

using namespace std;

class IndexError: public logic_error {
    public: IndexError(const string& message): logic_error(message) {}
};

template <typename T> class BlackBox {
    private:
    T* ptr;
    int size;
  
    public:
    BlackBox(T arr[], int s);
    T element_pop(int index, bool remove);
    void print();
    void push(T element);
    T pop();
    T xpop();
};



template <typename T> BlackBox<T>::BlackBox(T arr[], int s) {
    ptr = new T[s];
    size = s;
    for (size_t i = 0; i < size; i++) {
        ptr[i] = arr[i];
    }
}
  
template <typename T> void BlackBox<T>::print() {
    for (size_t i = 0; i < size; i++) {
        cout << *(ptr + i) << " ";
    }

    cout << endl;
}

template <typename T> void BlackBox<T>::push(T element) {
    ptr[size++] = element;
}

template <typename T> T BlackBox<T>::element_pop(int index, bool remove) {
    T element = ptr[index];

    if (remove) {
        size -= 1;

        for (size_t j = index; j < size; j++) {
            ptr[j] = ptr[j+1];
        }
    }

    return element;
}

template <typename T> T BlackBox<T>::pop() {
    if (size == 0) {
        throw IndexError("Out of range.");
    }

    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(0, size);

    return element_pop((rand() % size-1) + 1, true);
}

template <typename T> T BlackBox<T>::xpop() {
    if (size == 0) {
        throw IndexError("Out of range.");
    }

    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(0, size);

    return element_pop(dist6(rng), false);
}

int main(int argc, char** argv) {
    int arr[5] = { 1, 2, 3, 4, 5 };
    BlackBox<int> a(arr, 5);
    a.print();
    a.push(6);
    a.print();

    cout << a.pop() << endl;
    cout << a.pop() << endl;
    cout << a.pop() << endl;
    cout << a.pop() << endl;

    a.print();

    cout << a.pop() << endl;
    cout << a.pop() << endl;

    cout << a.pop() << endl;

    return 0;
}
