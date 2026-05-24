#include "linelist.h"
#include <iostream>
#include <chrono>

using namespace std;

int josephLineList(int N, int k) {
    LineList<int> lst;
    for (int i = N; i >= 1; --i) lst.pushFront(i);

    // частный случай удаляем все подряд
    if (k == 1) {
        while (!lst.empty()) lst.popFront();
        return -1;
    }

    lst.makeLoop(); // делаем кольцо
    auto* prev = lst.getFirst();
    int steps = k - 1;

    for (int i = 0; i < N - 1; ++i) {
        for (int s = 0; s < steps - 1; ++s) prev = prev->link;
        lst.eraseAfter(prev); // удаляем k-й эл
        prev = prev->link; // переходим к след
    }

    lst.breakLoop(prev);
    lst.setFirst(prev);
    return prev->value;
}

int main() {
    int N, k;
    cout << "введите N (количество) и k (шаг): ";
    cin >> N >> k;

    auto start = chrono::high_resolution_clock::now();
    int ans = josephLineList(N, k);
    auto end = chrono::high_resolution_clock::now();

    double elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000000.0;
    cout << "ответ: " << ans << endl;
    cout << "время: " << elapsed << " сек" << endl;

    return 0;
}