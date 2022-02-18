#ifndef VEC_HPP
#define VEC_HPP

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class Vec {
   private:
    // Size allocated
    std::size_t vecCapacity;
    // Number of elements
    std::size_t vecSize;
    T* arr;

   public:
    struct Iterator;

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
    T operator[](Iterator) const;

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

    // Access functions
    const T* data() const noexcept;
    T* data() noexcept;
    const T& front() const;
    T& front();
    const T& back() const;
    T& back();

    // Iterator functions
    Iterator begin();
    Iterator end();

    struct Iterator {
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

       private:
        pointer ptr;

       public:
        Iterator(pointer target);

        reference operator*();
        pointer raw();

        Iterator& operator++();
        Iterator operator++(int);
        Iterator operator+(const unsigned int moveLength);
        Iterator& operator--();
        Iterator operator--(int);
        Iterator operator-(const unsigned int moveLength);
        Iterator& operator[](const unsigned int index);

        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
            return lhs.ptr != rhs.ptr;
        }
        friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
            return lhs.ptr == rhs.ptr;
        }
    };
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

    T temp = data;
    arr[vecSize] = temp;
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
const T* Vec<T>::data() const noexcept {
    return arr;
}

template <typename T>
T* Vec<T>::data() noexcept {
    return arr;
}

template <typename T>
const T& Vec<T>::front() const {
    return &arr[0];
}

template <typename T>
T& Vec<T>::front() {
    return &arr[0];
}

template <typename T>
const T& Vec<T>::back() const {
    return &arr[vecSize];
}

template <typename T>
T& Vec<T>::back() {
    return &arr[vecSize];
}

template <typename T>
T Vec<T>::operator[](std::size_t index) const {
    if (index >= vecSize) {
        throw std::out_of_range("The given index is out of bounds.");
    }

    return arr[index];
}

template <typename T>
T Vec<T>::operator[](Iterator index) const {
    if (index >= vecSize) {
        throw std::out_of_range("The given index is out of bounds.");
    }

    return *index;
}

template <typename T>
auto Vec<T>::begin() -> Iterator {
    Iterator temp(&arr[0]);

    return temp;
}

template <typename T>
auto Vec<T>::end() -> Iterator {
    Iterator temp(&arr[vecSize]);

    return temp;
}

template <typename T>
Vec<T>::Iterator::Iterator(T* target) : ptr(target) {}

template <typename T>
T& Vec<T>::Iterator::operator*() {
    return *ptr;
}

template <typename T>
T* Vec<T>::Iterator::raw() {
    return ptr;
}

template <typename T>
auto Vec<T>::Iterator::operator++() -> Iterator& {
    ++ptr;
    return *this;
}

template <typename T>
auto Vec<T>::Iterator::operator++(int) -> Iterator {
    Iterator temp = *this;
    ++ptr;
    return temp;
}

template <typename T>
auto Vec<T>::Iterator::operator+(const unsigned int moveLength) -> Iterator {
    Iterator temp(ptr + moveLength);
    return temp;
}

template <typename T>
auto Vec<T>::Iterator::operator--() -> Iterator& {
    --ptr;
    return *this;
}

template <typename T>
auto Vec<T>::Iterator::operator--(int) -> Iterator {
    Iterator temp = *this;
    --ptr;
    return *temp;
}

template <typename T>
auto Vec<T>::Iterator::operator-(const unsigned int moveLength) -> Iterator {
    Iterator temp(ptr - moveLength);
    return temp;
}

template <typename T>
auto Vec<T>::Iterator::operator[](const unsigned int index) -> Iterator& {
    return *(ptr + index);
}

#endif  // VEC_HPP
