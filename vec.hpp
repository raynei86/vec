#ifndef VEC_HPP
#define VEC_HPP

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

constexpr std::size_t VEC_DEFAULT_SIZE = 5;

template <typename T> struct Vec {
    T* arr;
    std::size_t max{VEC_DEFAULT_SIZE};
    std::size_t curr{0};

    ~Vec() { delete[] arr; }

    Vec() {
        arr = new T[VEC_DEFAULT_SIZE];
        if (arr == nullptr) {
            throw std::bad_alloc();
        }
    }

    Vec(const std::size_t size) {
        arr = new T[size];
        max = size;
        if (arr == nullptr) {
            throw std::bad_array_new_length();
        }
    }

    Vec(std::initializer_list<T> l) {

        max = l.size();
        arr = new T[max];

        if (arr == nullptr) {
            throw std::bad_alloc();
        }

        std::size_t i = 0;
        for (auto it = l.begin(); it != l.end(); it++) {
            arr[i] = *it;
            i++;
        }
    }

    Vec(const Vec& other) {

        arr = new T[other.max];
        max = other.max;
        curr = other.curr;

        if (arr == nullptr) {
            throw std::bad_alloc();
        }

        for (std::size_t i = 0; i < other.max; i++) {
            this->arr[i] = other.arr[i];
        }
    }

    Vec& operator=(const Vec& other) { return Vec(other); }

    void push(T data) {
        if (curr >= max) {
            T* temp = new T[max * 2];
            if (temp == nullptr) {
                throw std::bad_alloc();
            }

            for (std::size_t i = 0; i < max; i++) {
                temp[i] = arr[i];
            }

            max *= 2;
            arr = temp;
        }

        arr[curr] = data;
        curr++;
    }

    Vec& operator[](std::size_t index) {
        if (index >= max) {
            throw std::out_of_range("The given index is out of bounds.");
        }

        return arr[index];
    }

    Vec& at(std::size_t index) {
        if (index >= max) {
            throw std::out_of_range("The given index is out of bounds.");
        }

        return arr[index];
    }

    T* begin() {
        T* temp = &arr[0];
        if (temp == nullptr) {
            throw std::bad_alloc();
        }

        return temp;
    }

    T* end() {
        T* temp = &arr[curr];
        if (temp == nullptr) {
            throw std::bad_alloc();
        }

        return temp;
    }
};
#endif // VEC_HPP
