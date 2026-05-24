#pragma once
#include "bmp_io.h"
#include <vector>
#include <queue>

// точка с координатами
struct tochka {
    int x, y;
    tochka(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
    bool operator==(const tochka& other) const { return x == other.x && y == other.y; }
};

// класс для лабиринта
class labirint {
private:
    std::vector<std::vector<bool>> stena; // true стена, а false проход
    int w, h;
    tochka start, finish;

public:
    labirint(const kartinka& img);
    std::vector<tochka> najti_put();
    void narisovat_put(kartinka& img, const std::vector<tochka>& put) const;
};