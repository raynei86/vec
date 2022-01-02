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

    Iterator<T>& operator++();
    Iterator<T> operator++(int);
    Iterator<T> operator+(const unsigned int moveLength);
    Iterator<T>& operator--();
    Iterator<T> operator--(int);
    Iterator<T> operator-(const unsigned int moveLength);

    bool operator!=(const Iterator<T>& other) const;
    bool operator==(const Iterator<T>& other) const;
    bool operator<(const Iterator<T>& other) const;
    bool operator<=(const Iterator<T>& other) const;
    bool operator>(const Iterator<T>& other) const;
    bool operator>=(const Iterator<T>& other) const;
};

template <typename T>
class ConstIterator : Iterator<T> {
   private:
    T* const ptr;
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
    Iterator<T> temp (ptr + moveLength);
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
    Iterator<T> temp (ptr - moveLength);
    return temp;
}

template <typename T>
T& Iterator<T>::operator*() {
    return *ptr;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator<T>& other) const {
    return ptr != other.ptr;
}

template <typename T>
bool Iterator<T>::operator==(const Iterator<T>& other) const {
    return ptr == other.ptr;
}

template <typename T>
bool Iterator<T>::operator<(const Iterator<T>& other) const {
    return ptr < other.ptr;
}

template <typename T>
bool Iterator<T>::operator<=(const Iterator<T>& other) const {
    return ptr <= other.ptr;
}

template <typename T>
bool Iterator<T>::operator>(const Iterator<T>& other) const {
    return ptr > other.ptr;
}

template <typename T>
bool Iterator<T>::operator>=(const Iterator<T>& other) const {
    return ptr >= other.ptr;
}

template <typename T>
T& Iterator<T>::data() {
    return *ptr;
}
#endif  // ITERATOR_HPP
