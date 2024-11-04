#include <iostream>
#include <cstdlib>


template <typename T>
class DynamicArray
{
private:
    T* data;
    std::size_t sz;
    std::size_t capacity;

    static const std::size_t REALLOC_STEP = 2;

public:
    DynamicArray() : data(nullptr), sz(0), capacity(0) {}
    DynamicArray(const DynamicArray& other) {
        copy(other);
    }

    DynamicArray& operator= (const DynamicArray& other) {
        if (this != &other) {
            free();
            copy(other);
        }

        return *this;
    }

    ~DynamicArray() {
        free();
    }

    void push_back(const T& elem) {
        //TO DO
    }

    void pop_back() {
        //TO DO
    }

    std::size_t size() const {
        return sz;
    }

    T& operator[] (std::size_t idx) {
        return data[idx];
    }

    const T& operator[] (std::size_t idx) const {
        return data[idx];
    }

private:
    void free() {
        delete[] data;
        data = nullptr;
        sz = 0;
        capacity = 0;
    }

    void copy(const DynamicArray& other) {
        if (other.capacity == 0) {
            *this = DynamicArray();

            return;
        }

        data = new T[other.capacity];
        capacity = other.capacity;
        for (sz = 0; sz < other.sz; ++sz) {
            data[sz] = other[sz];
        }
    }

    void reserve(std::size_t n) {
        T* buffer = new T[n];

        for (std::size_t i = 0; i < sz; ++i) {
            buffer[i] = data[i];
        }

        delete[] data;
        data = buffer;
        capacity = n;
    }

};

int main() {
    return 0;
}
