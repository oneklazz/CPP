// замер времени для всех N из таблицы
#include "array.h"
#include "linelist.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <sys/stat.h>

using namespace std;

void makeDir(const char* path) {
    mkdir(path, 0777);
}

int josephArray(int N, int k) {
    Array<int> arr;
    for (int i = 1; i <= N; ++i) arr.append(i);
    int pos = 0;
    while (arr.size() > 1) {
        pos = (pos + k - 1) % arr.size();
        arr.eraseAt(pos);
    }
    return arr[0];
}

int josephLineList(int N, int k) {
    LineList<int> lst;
    for (int i = N; i >= 1; --i) lst.pushFront(i);
    if (k == 1) {
        while (!lst.empty()) lst.popFront();
        return -1;
    }
    lst.makeLoop();
    auto* prev = lst.getFirst();
    int steps = k - 1;
    for (int i = 0; i < N - 1; ++i) {
        for (int s = 0; s < steps - 1; ++s) prev = prev->link;
        lst.eraseAfter(prev);
        prev = prev->link;
    }
    lst.breakLoop(prev);
    lst.setFirst(prev);
    return prev->value;
}

int main() {
    int sizes[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    int k = 2;

    makeDir("results");

    ofstream arrOut("results/array_results.csv");
    ofstream listOut("results/linelist_results.csv");

    arrOut << "N;Ответ;Время расчета(сек)" << endl;
    listOut << "N;Ответ;Время расчета(сек)" << endl;

    for (int n : sizes) {
        cout << "n = " << n << endl;

        auto start = chrono::high_resolution_clock::now();
        int arrAns = josephArray(n, k);
        auto end = chrono::high_resolution_clock::now();
        double arrTime = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000000.0;

        start = chrono::high_resolution_clock::now();
        int listAns = josephLineList(n, k);
        end = chrono::high_resolution_clock::now();
        double listTime = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000000.0;

        arrOut << n << ";" << arrAns << ";" << arrTime << endl;
        listOut << n << ";" << listAns << ";" << listTime << endl;

        cout << "  array: " << arrTime << " сек" << endl;
        cout << "  linelist: " << listTime << " сек" << endl;
    }

    arrOut.close();
    listOut.close();
    cout << "\nготово!" << endl;

    return 0;
}