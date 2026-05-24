#pragma once
#include <iostream>

template <typename T>
class LineList {
private:
    struct Item {
        T value;
        Item* link;
        Item(const T& val, Item* next = nullptr) : value(val), link(next) {}
    };
    Item* first; // указатель на первый элемент

public:
    LineList();
    ~LineList();

    // базовые операции со списком
    void pushFront(const T& val);
    void insertAfter(Item* pos, const T& val);
    void popFront();
    void eraseAfter(Item* pos);

    // доступ к началу и проверка
    Item* getFirst() const;
    bool empty() const;

    // для кольцевой структуры
    void makeLoop();
    void breakLoop(Item* last);
    void setFirst(Item* newFirst);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const LineList<U>& lst);
};