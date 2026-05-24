#pragma once
#include <iostream>

class BadIndex {};

template <typename T>
class Array {
private:
    T* store; // хранилище элем
    int count; // текущее колво
    int capacity; // выделенная вместимость

    void expand(int needed);

public:
    explicit Array(int startCapacity = 10);
    Array(const Array& other);
    ~Array();

    Array& operator=(const Array& other);
    T& operator[](int idx);
    const T& operator[](int idx) const;

    int size() const;
    bool empty() const;

    // операции с массивом
    void append(const T& val);
    void removeLast();
    void insertAt(int idx, const T& val);
    void eraseAt(int idx);

    void clear();

    friend std::ostream& operator<<(std::ostream& out, const Array<T>& arr) {
        for (int i = 0; i < arr.count; ++i) out << arr.store[i] << " ";
        return out;
    }
};