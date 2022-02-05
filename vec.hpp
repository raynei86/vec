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
    // Size allocated
    std::size_t vecCapacity;
    // Number of elements
    std::size_t vecSize;
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
    void erase(std::size_t index);
    void resize(const std::size_t newSize);
    void reserve(const std::size_t newCap);
    void insert(std::size_t index, const T data);

    // Getters
    std::size_t size() const;
    std::size_t capacity() const;

    // Iterator functions
    Iterator<T> begin();
    Iterator<T> end();
};

// Default constructor will set size and capacity to 0 and array to a nullptr
template <typename T>
Vec<T>::Vec() : vecCapacity(0), vecSize(0), arr(nullptr) {}

template <typename T>
Vec<T>::Vec(const std::size_t size)
    : vecCapacity(size),
      vecSize(0),
      arr(static_cast<T*>(std::malloc(sizeof(T) * size))) {
    if (arr == nullptr) {
        throw std::bad_array_new_length();
    }
}

template <typename T>
Vec<T>::Vec(std::initializer_list<T> l)
    : vecCapacity(l.size()),
      vecSize(vecCapacity),
      arr(static_cast<T*>(std::malloc(sizeof(T) * vecCapacity))) {
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
    : vecCapacity(other.vecCapacity),
      vecSize(other.vecSize),
      arr(static_cast<T*>(std::malloc(sizeof(T) * vecCapacity))) {
    if (arr == nullptr) {
        throw std::bad_alloc();
    }

    for (std::size_t i = 0; i < other.vecCapacity; i++) {
        this->arr[i] = other.arr[i];
    }
}

template <typename T>
Vec<T>::Vec(const Vec&& other) noexcept
    : vecCapacity(0), vecSize(0), arr(nullptr) {
    other.swap(*this);
}

template <typename T>
Vec<T>::~Vec() {
    if (arr != nullptr) {
        std::free(arr);
    }
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
    if (vecSize >= vecCapacity) {
        reserve(vecCapacity * 2);
    }

    arr[vecSize] = data;
    vecSize++;
}

template <typename T>
void Vec<T>::pop_back() {
    if (vecSize == 0) {
        throw std::underflow_error("Can not pop nothing.");
    }

    resize(vecSize - 1);
}

template <typename T>
void Vec<T>::swap(Vec& other) {
    std::swap(arr, other.arr);
    std::swap(vecSize, other.vecSize);
    std::swap(vecCapacity, other.vecCapacity);
}

template <typename T>
void Vec<T>::clear() {
    vecSize = 0;
    std::free(arr);
    arr = static_cast<T*>(std::malloc(sizeof(T) * vecCapacity));
}

template <typename T>
void Vec<T>::erase(std::size_t index) {
    if (index > vecSize) {
        throw std::out_of_range("Cannot erase beyond vector.");
    }

    for (auto i = index; i <= vecSize - 1; i++) {
        arr[i] = arr[i + 1];
    }

    resize(vecSize - 1);
}

template <typename T>
void Vec<T>::resize(const std::size_t newSize) {
    if (newSize < 0) {
        throw std::length_error("Can not resize below zero.");
    }

    if (newSize > vecSize) {
        // This seems like a really stupid solution
        arr = static_cast<T*>(std::realloc(arr, newSize));
        arr = static_cast<T*>(std::realloc(arr, vecCapacity));
    }
    vecSize = newSize;
}

template <typename T>
void Vec<T>::reserve(const std::size_t newCap) {
    if (newCap <= vecCapacity) {
        return;
    }

    if (newCap <= 0) {
        clear();
    }

    vecCapacity = newCap;
    arr = static_cast<T*>(std::realloc(arr, sizeof(T) * vecCapacity));
}

template <typename T>
void Vec<T>::insert(std::size_t index, const T data) {
    ++vecSize;

    if (vecSize >= vecCapacity) {
        resize(vecSize + 1);
    }

    if (index > vecSize) {
        throw std::out_of_range("Cannot insert beyond vector.");
    }

    // Shift every element to the right to make space for insertion
    for (auto i = vecSize - 1; i > index; --i) {
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
