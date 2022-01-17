#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <stdexcept>

template <typename T>
class Iterator {
   private:
    T* ptr;

   public:
    Iterator();
    Iterator(T* target);
    ~Iterator();

    T& data();
    T& operator*();
    T* raw();

    Iterator<T>& operator++();
    Iterator<T> operator++(int);
    Iterator<T> operator+(const unsigned int moveLength);
    Iterator<T>& operator--();
    Iterator<T> operator--(int);
    Iterator<T> operator-(const unsigned int moveLength);
    T& operator[](const unsigned int index);

    bool operator!=(const Iterator<T>& rhs) const;
    bool operator==(const Iterator<T>& rhs) const;
    bool operator<(const Iterator<T>& rhs) const;
    bool operator<=(const Iterator<T>& rhs) const;
    bool operator>(const Iterator<T>& rhs) const;
    bool operator>=(const Iterator<T>& rhs) const;
};

template <typename T>
Iterator<T>::Iterator() : ptr(nullptr) {}

template <typename T>
Iterator<T>::Iterator(T* target) : ptr(target) {
    if (ptr == nullptr) {
        throw std::bad_alloc();
    }
}

template <typename T>
Iterator<T>::~Iterator() = default;

template <typename T>
Iterator<T>& Iterator<T>::operator++() {
    ptr++;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int) {
    Iterator<T> temp = *this;
    ptr++;
    return temp;
}

template <typename T>
Iterator<T> Iterator<T>::operator+(const unsigned int moveLength) {
    Iterator<T> temp(ptr + moveLength);
    return temp;
}

template <typename T>
Iterator<T>& Iterator<T>::operator--() {
    ptr--;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator--(int) {
    Iterator<T> temp = *this;
    ptr++;
    return temp;
}

template <typename T>
Iterator<T> Iterator<T>::operator-(const unsigned int moveLength) {
    Iterator<T> temp(ptr - moveLength);
    return temp;
}

template <typename T>
T& Iterator<T>::operator[](const unsigned int index) {
    return *(ptr + index);
}

template <typename T>
T& Iterator<T>::operator*() {
    return *ptr;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator<T>& rhs) const {
    return ptr != rhs.ptr;
}

template <typename T>
bool Iterator<T>::operator==(const Iterator<T>& rhs) const {
    return ptr == rhs.ptr;
}

template <typename T>
bool Iterator<T>::operator<(const Iterator<T>& rhs) const {
    return ptr < rhs.ptr;
}

template <typename T>
bool Iterator<T>::operator<=(const Iterator<T>& other) const {
    return ptr <= other.ptr;
}

template <typename T>
bool Iterator<T>::operator>(const Iterator<T>& rhs) const {
    return ptr > rhs.ptr;
}

template <typename T>
bool Iterator<T>::operator>=(const Iterator<T>& rhs) const {
    return ptr >= rhs.ptr;
}

template <typename T>
T& Iterator<T>::data() {
    return *ptr;
}

template <typename T>
T* Iterator<T>::raw() {
    return ptr;
}
#endif  // ITERATOR_HPP
