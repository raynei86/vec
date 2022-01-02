#ifndef VEC_HPP
#define VEC_HPP

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

#include "iterator.hpp"

// TODO: Const operators
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
    void swap(Vec& other);
    void clear();
    void erase(Iterator<T> itr);
    void resize(const std::size_t newSize);
    void insert(const std::size_t index, const T data);

    std::size_t size() const;
    std::size_t capacity() const;

    Iterator<T> begin() const;
    Iterator<T> end() const;
};

template <typename T>
Vec<T>::Vec() : vecSize(), vecCapacity(), arr(nullptr) {}

template <typename T>
Vec<T>::Vec(const std::size_t size)
    : vecSize(size), vecCapacity(0), arr(new T[size]) {
    if (arr == nullptr) {
        throw std::bad_array_new_length();
    }
}

template <typename T>
Vec<T>::Vec(std::initializer_list<T> l)
    : vecSize(l.size()), vecCapacity(vecSize), arr(new T[vecSize]) {
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
Vec<T>::~Vec() = default;

template <typename T>
Vec<T>& Vec<T>::operator=(const Vec& other) {
    delete[] arr;

    vecSize = other.vecSize;
    vecCapacity = other.vecCapacity;
    arr = new T[vecCapacity];

    if (arr == nullptr) {
        throw std::bad_alloc();
    }

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

        for (std::size_t i = 0; i < vecCapacity; i++) {
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
    T* temp = new T[vecSize - 1];
    if (temp == nullptr) {
        throw std::bad_alloc();
    }

    for (std::size_t i = 0; i < vecCapacity - 1; i++) {
        temp[i] = arr[i];
    }

    delete[] arr;
    vecSize--;
    arr = temp;
}

template <typename T>
void Vec<T>::swap(Vec& other) {
    int tempSize;
    int tempCapacity;
    T* tempArr;

    tempSize = other.vecSize;
    tempCapacity = other.vecCapacity;
    tempArr = other.arr;

    other.vecSize = vecSize;
    other.vecCapacity = vecCapacity;
    other.arr = arr;

    vecSize = tempSize;
    vecCapacity = tempCapacity;
    arr = tempArr;
}

template <typename T>
void Vec<T>::clear() {
    delete[] arr;
    arr = new T[vecSize];
}

template <typename T>
void Vec<T>::erase(Iterator<T> itr) {
    if (itr > end()) {
        throw std::out_of_range("Cannot erase beyond vector.");
    }

    for (auto i = itr; i <= end() - 1; i++) {
        *i = *(i + 1);
    }
    resize(vecSize - 1);
}

template <typename T>
void Vec<T>::resize(const std::size_t newSize) {
    vecSize = newSize;
    T* temp = new T[newSize];

    for (std::size_t i = 0; i <= newSize; i++) {
        temp[i] = arr[i];
    }

    delete[] arr;
    arr = temp;
}

template <typename T>
void Vec<T>::insert(const std::size_t index, const T data) {
    if (vecCapacity == vecSize) {
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

    if (index > vecSize) {
        throw std::out_of_range("Cannot insert beyond vector.");
    }

    for (std::size_t i = vecSize - 1; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = data;
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
Iterator<T> Vec<T>::begin() const {
    Iterator<T> temp(&arr[0]);

    return temp;
}

template <typename T>
Iterator<T> Vec<T>::end() const {
    Iterator<T> temp(&arr[vecSize]);

    return temp;
}
#endif  // VEC_HPP
