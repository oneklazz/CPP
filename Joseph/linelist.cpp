#include "linelist.h"

template <typename T>
LineList<T>::LineList() : first(nullptr) {}

template <typename T>
LineList<T>::~LineList() {
    while (!empty()) popFront();
}

// добавление в начало
template <typename T>
void LineList<T>::pushFront(const T& val) {
    first = new Item(val, first);
}

// вставка после заданного элемента
template <typename T>
void LineList<T>::insertAfter(Item* pos, const T& val) {
    if (!pos) return;
    pos->link = new Item(val, pos->link);
}

// удаление первого элемента
template <typename T>
void LineList<T>::popFront() {
    if (!first) return;
    Item* tmp = first;
    first = first->link;
    delete tmp;
}

// удаление элемента после заданного
template <typename T>
void LineList<T>::eraseAfter(Item* pos) {
    if (!pos || !pos->link) return;
    Item* tmp = pos->link;
    pos->link = tmp->link;
    delete tmp;
}

template <typename T>
typename LineList<T>::Item* LineList<T>::getFirst() const {
    return first;
}

template <typename T>
bool LineList<T>::empty() const {
    return first == nullptr;
}

// превращаем список в кольцо (то есть последний указывает на первый)
template <typename T>
void LineList<T>::makeLoop() {
    if (!first) return;
    Item* cur = first;
    while (cur->link) cur = cur->link;
    cur->link = first;
}

// разрываем кольцо
template <typename T>
void LineList<T>::breakLoop(Item* last) {
    if (last) last->link = nullptr;
}

template <typename T>
void LineList<T>::setFirst(Item* newFirst) {
    first = newFirst;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const LineList<T>& lst) {
    auto cur = lst.first;
    if (!cur) {
        out << "empty";
    } else {
        out << cur->value;
    }
    return out;
}

template class LineList<int>;