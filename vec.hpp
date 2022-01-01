#ifndef VEC_HPP
#define VEC_HPP

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

// TODO: Const operators
// TODO: Move constructor
// TODO: Implement allocator
// TODO: Incorporate Iterators
// TODO: Implement all the other functions

template <typename T>
class Vec {
   private:
    std::size_t vecSize;
    std::size_t vecCapacity;
    T* arr;

   public:
    Vec();
    Vec(std::size_t size);
    Vec(const std::initializer_list<T> l);
    Vec(const Vec& other);
    Vec(const Vec&& other);
    ~Vec();

    Vec& operator=(const Vec& other);
    Vec& operator=(const Vec&& other);
    T operator[](std::size_t index) const;

    void push_back(const T data);
    void pop_back();

    std::size_t size() const;
    std::size_t capacity() const;

    T* begin() const;
    T* end() const;
};

template <typename T>
Vec<T>::Vec() : vecSize(), vecCapacity(), arr(nullptr) {}

template <typename T>
Vec<T>::Vec(const std::size_t size) : vecSize(size), arr(new T[size]) {
    if (arr == nullptr) {
        throw std::bad_array_new_length();
    }
}

template <typename T>
Vec<T>::Vec(std::initializer_list<T> l) : vecSize(l.size), arr(new T[vecSize]) {
    if (arr == nullptr) {
        throw std::bad_alloc();
    }

    std::size_t i = 0;
    for (auto it = l.begin(); it != l.end(); it++) {
        arr[i] = *it;
        i++;
    }
}

template <typename T>
Vec<T>::Vec(const Vec& other)
    : vecSize(other.vecSize),
      vecCapacity(other.vecCapacity),
      arr(new T[vecSize]) {
    if (arr == nullptr) {
        throw std::bad_alloc();
    }

    for (std::size_t i = 0; i < other.vecSize; i++) {
        this->arr[i] = other.arr[i];
    }
}

template <typename T>
Vec<T>::Vec(const Vec&& other)
    : vecSize(other.vecSize), vecCapacity(other.vecCapacity), arr(other.arr) {

    other.arr = nullptr;
    other.vecSize = 0;
    other.vecCapacity = 0;
}

template <typename T>
Vec<T>::~Vec() {
    delete[] arr;
}

template <typename T>
Vec<T>& Vec<T>::operator=(const Vec& other) {
    delete [] arr;

    vecSize = other.vecSize;
    vecCapacity = other.vecCapacity;
    arr = new T[vecCapacity];

    for (int i = 0; i < vecCapacity; i++) {
       arr[i] = other.arr[i];
    }
}

template <typename T>
Vec<T>& Vec<T>::operator=(const Vec<T>&& other) {
    delete[] arr;

    vecSize = other.vecSize;
    vecCapacity = other.vecCapacity;
    arr = other.arr;

    other.arr = nullptr;
    other.vecSize = 0;
    other.vecCapacity = 0;

    return *this;
}

template <typename T>
void Vec<T>::push_back(const T data) {
    if (vecCapacity >= vecSize) {
        T* temp = new T[vecSize + 5];
        if (temp == nullptr) {
            throw std::bad_alloc();
        }

        for (std::size_t i = 0; i < vecSize; i++) {
            temp[i] = arr[i];
        }

        delete[] arr;
        vecSize += 5;
        arr = temp;
    }

    arr[vecCapacity] = data;
    vecCapacity++;
}

template <typename T>
void Vec<T>::pop_back() {
    if (vecCapacity == 0) {
        throw std::underflow_error("Can not pop nothing.");
    }
    vecCapacity--;
}

template <typename T>
std::size_t Vec<T>::size() const {
    return vecSize;
}

template <typename T>
std::size_t Vec<T>::capacity() const {
    return vecCapacity;
}

template <typename T>
T Vec<T>::operator[](std::size_t index) const {
    if (index >= vecSize) {
        throw std::out_of_range("The given index is out of bounds.");
    }

    return arr[index];
}

template <typename T>
T* Vec<T>::begin() const {
    T* temp = &arr[0];
    if (temp == nullptr) {
        throw std::bad_alloc();
    }

    return temp;
}

template <typename T>
T* Vec<T>::end() const {
    T* temp = &arr[vecCapacity];
    if (temp == nullptr) {
        throw std::bad_alloc();
    }

    return temp;
}
#endif  // VEC_HPP
