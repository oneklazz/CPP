#include "array.h"

// увелич вместимости
template <typename T>
void Array<T>::expand(int needed) {
    if (needed <= capacity) return;
    int newCap = capacity * 2;
    if (newCap < needed) newCap = needed;

    T* newStore = new T[newCap];
    for (int i = 0; i < count; ++i) newStore[i] = store[i];
    delete[] store;
    store = newStore;
    capacity = newCap;
}

template <typename T>
Array<T>::Array(int startCapacity) {
    if (startCapacity <= 0) startCapacity = 10;
    capacity = startCapacity;
    store = new T[capacity];
    count = 0;
}

// конструктор копирования
template <typename T>
Array<T>::Array(const Array& other) {
    capacity = other.capacity;
    count = other.count;
    store = new T[capacity];
    for (int i = 0; i < count; ++i) store[i] = other.store[i];
}

template <typename T>
Array<T>::~Array() {
    delete[] store;
}

// оператор присваивания
template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this == &other) return *this;
    if (capacity != other.capacity) {
        delete[] store;
        capacity = other.capacity;
        store = new T[capacity];
    }
    count = other.count;
    for (int i = 0; i < count; ++i) store[i] = other.store[i];
    return *this;
}

// доступ по индексу
template <typename T>
T& Array<T>::operator[](int idx) {
    if (idx < 0 || idx >= count) throw BadIndex();
    return store[idx];
}

template <typename T>
const T& Array<T>::operator[](int idx) const {
    if (idx < 0 || idx >= count) throw BadIndex();
    return store[idx];
}

template <typename T>
int Array<T>::size() const {
    return count;
}

template <typename T>
bool Array<T>::empty() const {
    return count == 0;
}

// добавление в конец
template <typename T>
void Array<T>::append(const T& val) {
    if (count == capacity) expand(count + 1);
    store[count++] = val;
}

// удаление последнего
template <typename T>
void Array<T>::removeLast() {
    if (count == 0) throw BadIndex();
    count--;
}

// вставка со сдвигом по индексу
template <typename T>
void Array<T>::insertAt(int idx, const T& val) {
    if (idx < 0 || idx > count) throw BadIndex();
    if (count == capacity) expand(count + 1);
    for (int i = count; i > idx; --i) store[i] = store[i - 1];
    store[idx] = val;
    count++;
}

// удаление тоже со сдвигом по индексу
template <typename T>
void Array<T>::eraseAt(int idx) {
    if (idx < 0 || idx >= count) throw BadIndex();
    for (int i = idx; i < count - 1; ++i) store[i] = store[i + 1];
    count--;
}

template <typename T>
void Array<T>::clear() {
    count = 0;
}

template class Array<int>;