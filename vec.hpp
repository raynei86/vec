#ifndef VEC_HPP
#define VEC_HPP

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <initializer_list>
#include <stdexcept>

#include "iterator.hpp"

template <typename T>
class Vec {
   private:
    // Capacity is how much elemnts the vector has.
    // Size is the size allocated.
    std::size_t vecSize;
    std::size_t vecCapacity;
    T* arr;

   public:
    // Constructors
    Vec();
    Vec(std::size_t size);
    Vec(const std::initializer_list<T> l);
    Vec(const Vec& other);
    Vec(const Vec&& other) noexcept;
    ~Vec();

    // Operators
    Vec& operator=(const Vec& other);
    Vec& operator=(const Vec&& other) noexcept;
    T operator[](std::size_t index) const;
    T operator[](Iterator<T>) const;

    // Modifier functions
    void push_back(const T data);
    void pop_back();
    void swap(Vec& other);
    void clear();
    void erase(Iterator<T> pos);
    void resize(const std::size_t newSize);
    void insert(Iterator<T> pos, const T data);

    // Getters
    std::size_t size() const;
    std::size_t capacity() const;

    // Iterator functions
    Iterator<T> begin();
    Iterator<T> end();
};

// Default constructor will set size and capacity to 0 and array to a nullptr
template <typename T>
Vec<T>::Vec() : vecSize(0), vecCapacity(0), arr(nullptr) {}

template <typename T>
Vec<T>::Vec(const std::size_t size)
    : vecSize(size),
      vecCapacity(0),
      arr(static_cast<T*>(std::malloc(sizeof(T) * size))) {
    if (arr == nullptr) {
        throw std::bad_array_new_length();
    }
}

template <typename T>
Vec<T>::Vec(std::initializer_list<T> l)
    : vecSize(l.size()),
      vecCapacity(vecSize),
      arr(static_cast<T*>(std::malloc(sizeof(T) * vecSize))) {
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
      arr(static_cast<T*>(std::malloc(sizeof(T) * vecSize))) {
    if (arr == nullptr) {
        throw std::bad_alloc();
    }

    for (std::size_t i = 0; i < other.vecSize; i++) {
        this->arr[i] = other.arr[i];
    }
}

template <typename T>
Vec<T>::Vec(const Vec&& other) noexcept
    : vecSize(0), vecCapacity(0), arr(nullptr) {
    other.swap(*this);
}

template <typename T>
Vec<T>::~Vec() {
    std::free(arr);
}

template <typename T>
Vec<T>& Vec<T>::operator=(const Vec& other) {
    Vec<T> copy(other);
    copy.swap(*this);
    return *this;
}

template <typename T>
Vec<T>& Vec<T>::operator=(const Vec<T>&& other) noexcept {
    other.swap(*this);
    return *this;
}

template <typename T>
void Vec<T>::push_back(const T data) {
    if (vecCapacity >= vecSize) {
        resize(vecSize * 2);
    }

    arr[vecCapacity] = data;
    vecCapacity++;
}

template <typename T>
void Vec<T>::pop_back() {
    if (vecCapacity == 0) {
        throw std::underflow_error("Can not pop nothing.");
    }

    resize(vecSize - 1);
}

template <typename T>
void Vec<T>::swap(Vec& other) {
    std::swap(arr, other.arr);
    std::swap(vecCapacity, other.vecCapacity);
    std::swap(vecSize, other.vecSize);
}

template <typename T>
void Vec<T>::clear() {
    ~Vec();
    arr = static_cast<T*>(std::malloc(sizeof(T) * vecSize));
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
    arr = static_cast<T*>(std::realloc(arr, sizeof(T) * vecSize));
}

template <typename T>
void Vec<T>::insert(Iterator<T> pos, const T data) {
    if (vecCapacity >= vecSize) {
        resize(vecSize + 1);
    }

    if (pos > end()) {
        throw std::out_of_range("Cannot insert beyond vector.");
    }

    // Shift every element to the right to make space for insertion
    for (auto i = end() - 1; i >= pos; --i) {
        *i = *(i - 1);
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
    Iterator<T> temp(&arr[0]);

    return temp;
}

template <typename T>
Iterator<T> Vec<T>::end() {
    Iterator<T> temp(&arr[vecSize]);

    return temp;
}
#endif  // VEC_HPP
