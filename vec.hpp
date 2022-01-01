#ifndef VEC_HPP
#define VEC_HPP

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

 // TODO: Const operators
 // TODO: Move constructor
 // TODO: Implement allocator
 // TODO: Incorporate Iterators
 // TODO: Implement all the other functions

template <typename T>
class Vec {
   private:
    std::size_t max;
    std::size_t capacity;
    T* arr;

   public:
    Vec();
    Vec(std::size_t size);
    Vec(std::initializer_list<T> l);
    Vec(const Vec& other);
    ~Vec();

    Vec& operator=(const Vec& other) const;
    T operator[](std::size_t index) const;

    void push_back(const T data);
    void pop_back();

    std::size_t size() const;

    T* begin() const;
    T* end() const;
};

template <typename T>
Vec<T>::Vec() : max(), capacity(), arr(nullptr) {}

template <typename T>
Vec<T>::Vec(const std::size_t size) : max(size), arr(new T[size]) {
    if (arr == nullptr) {
        throw std::bad_array_new_length();
    }
}

template <typename T>
Vec<T>::Vec(std::initializer_list<T> l) : max(l.size), arr(new T[max]) {
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
    : max(other.max), capacity(other.capacity), arr(new T[max]) {
    if (arr == nullptr) {
        throw std::bad_alloc();
    }

    for (std::size_t i = 0; i < other.max; i++) {
        this->arr[i] = other.arr[i];
    }
}

template <typename T>
Vec<T>::~Vec() {
    delete[] arr;
}

template <typename T>
Vec<T>& Vec<T>::operator=(const Vec& other) const {
    return Vec(other);
}

template <typename T>
void Vec<T>::push_back(const T data) {
    if (capacity >= max) {
        T* temp = new T[max + 5];
        if (temp == nullptr) {
            throw std::bad_alloc();
        }

        for (std::size_t i = 0; i < max; i++) {
            temp[i] = arr[i];
        }

        delete [] arr;
        max += 5;
        arr = temp;
    }

    arr[capacity] = data;
    capacity++;
}

template <typename T>
void Vec<T>::pop_back() {
    if (capacity == 0) {
        throw std::underflow_error("Can not pop nothing.");
    }
    capacity--;
}

template <typename T>
std::size_t Vec<T>::size() const {
   return max;
}

template <typename T>
T Vec<T>::operator[](std::size_t index) const {
    if (index >= max) {
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
    T* temp = &arr[capacity];
    if (temp == nullptr) {
        throw std::bad_alloc();
    }

    return temp;
}
#endif  // VEC_HPP
