#ifndef VEC_HPP
#define VEC_HPP

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>

#include "iterator.hpp"

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
    T operator[](Iterator<T>) const;

    void push_back(const T data);
    void pop_back();
    void swap(Vec& other);
    void clear();
    void erase(Iterator<T> pos);
    void resize(const std::size_t newSize);
    void insert(Iterator<T> pos, const T data);

    std::size_t size() const;
    std::size_t capacity() const;

    Iterator<T> begin();
    Iterator<T> end();
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
    : vecSize(0), vecCapacity(0), arr(nullptr) {
    other.swap(*this);
}

template <typename T>
Vec<T>::~Vec() = default;

template <typename T>
Vec<T>& Vec<T>::operator=(const Vec& other) {
    Vec<T> copy(other);
    copy.swap(*this);
    return *this;
}

template <typename T>
Vec<T>& Vec<T>::operator=(const Vec<T>&& other) {
    other.swap(*this);
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
    std::swap(arr, other.arr);
    std::swap(vecCapacity, other.vecCapacity);
    std::swap(vecSize, other.vecSize);
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
    if (newSize < 0) {
        throw std::length_error("Can not resize below zero.");
    }

    vecSize = newSize;
    T* temp = new T[newSize];

    for (std::size_t i = 0; i <= newSize; i++) {
        temp[i] = arr[i];
    }

    delete[] arr;
    arr = temp;
    vecSize = newSize;
}

template <typename T>
void Vec<T>::insert(Iterator<T> pos, const T data) {
    if (vecCapacity >= vecSize) {
       resize(vecSize + 1);
    }

    if (pos > end()) {
        throw std::out_of_range("Cannot insert beyond vector.");
    }

    for (auto i = pos + 1; i < end(); i++) {
        *i = *(++i);
    }

    *pos = data;
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
T Vec<T>::operator[](Iterator<T> index) const {
    if (index >= vecSize) {
        throw std::out_of_range("The given index is out of bounds.");
    }

    return *index;
}

template <typename T>
Iterator<T> Vec<T>::begin() {
    Iterator<T> temp(arr);

    return temp;
}

template <typename T>
Iterator<T> Vec<T>::end() {
    Iterator<T> temp(arr + vecSize);

    return temp;
}
#endif  // VEC_HPP
