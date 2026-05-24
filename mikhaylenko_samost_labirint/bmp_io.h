#pragma once
#include <vector>
#include <string>

// простой цвет
struct cvet {
    unsigned char r, g, b;
    cvet(unsigned char r_ = 0, unsigned char g_ = 0, unsigned char b_ = 0) : r(r_), g(g_), b(b_) {}
};

// класс для картинки
class kartinka {
private:
    int w, h;
    std::vector<cvet> pikseli;

public:
    kartinka(int w_, int h_);
    bool zagruzit(const std::string& imya);
    bool sohranit(const std::string& imya) const;
    
    int get_w() const { return w; }
    int get_h() const { return h; }
    
    cvet get_piksel(int x, int y) const;
    void set_piksel(int x, int y, const cvet& c);
};