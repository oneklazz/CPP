#include "array.h"
#include <iostream>
#include <chrono>

using namespace std;

int josephArray(int N, int k) {
    Array<int> arr;
    for (int i = 1; i <= N; ++i) arr.append(i);

    int pos = 0;
    // удаляем каждый k-й, пока не останется один
    while (arr.size() > 1) {
        pos = (pos + k - 1) % arr.size();
        arr.eraseAt(pos);
    }
    return arr[0];
}

int main() {
    int N, k;
    cout << "введите N (количество) и k (шаг): ";
    cin >> N >> k;

    auto start = chrono::high_resolution_clock::now();
    int ans = josephArray(N, k);
    auto end = chrono::high_resolution_clock::now();

    double elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000000.0;
    cout << "ответ: " << ans << endl;
    cout << "время: " << elapsed << " сек" << endl;

    return 0;
}