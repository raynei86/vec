#ifndef ITERATOR_HPP
#define ITERATOR_HPP

template <typename T>
class Iterator {
   private:
    T* ptr;

   public:
    Iterator();
    Iterator(T* target);
    ~Iterator();

    void operator++();
    void operator+(const unsigned int moveLength);
    void operator--();
    void operator-(const unsigned int moveLength);
    T& operator*();
};

template <typename T>
Iterator<T>::Iterator() : ptr(nullptr) {}

template <typename T>
Iterator<T>::Iterator(T* target) : ptr(target) {}

template <typename T>
Iterator<T>::~Iterator() {
    delete ptr;
}

template <typename T>
void Iterator<T>::operator++() {
ptr++;
}

template <typename T>
void Iterator<T>::operator+(const unsigned int moveLength) {
    ptr += moveLength;
}

template <typename T>
void Iterator<T>::operator--() {
ptr--;
}

template <typename T>
void Iterator<T>::operator-(const unsigned int moveLength) {
   return ptr -= moveLength;
}

template <typename T>
T& Iterator<T>::operator*() {
    return *ptr;
}

#endif  // ITERATOR_HPP
