#include "labirint.h"
#include <algorithm>
#include <iostream>

labirint::labirint(const kartinka& img) {
    w = img.get_w();
    h = img.get_h();
    stena.resize(h, std::vector<bool>(w, false));

    bool start_najden = false;
    bool finish_najden = false;

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            cvet c = img.get_piksel(x, y);
            
            // определяем стены (чёрный)
            int yarkost = c.r + c.g + c.b;
            if (yarkost < 50) {
                stena[y][x] = true;
            } else {
                stena[y][x] = false;
            }
            
            // ищем зелёный вход (зелёный канал самый яркий)
            if (c.g > c.r && c.g > c.b && c.g > 100) {
                start = tochka(x, y);
                start_najden = true;
                stena[y][x] = false;
            }
            
            // ищем красный выход (красный канал тожн самый яркий)
            if (c.r > c.g && c.r > c.b && c.r > 100) {
                finish = tochka(x, y);
                finish_najden = true;
                stena[y][x] = false;
            }
        }
    }

    // если вход не найден то пробуем найти просто яркий зелёный
    if (!start_najden) {
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                cvet c = img.get_piksel(x, y);
                if (c.g > 150 && c.r < 100 && c.b < 100) {
                    start = tochka(x, y);
                    start_najden = true;
                    stena[y][x] = false;
                    break;
                }
            }
            if (start_najden) break;
        }
    }

    // если выход не найден то пробуем просто яркий красный
    if (!finish_najden) {
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                cvet c = img.get_piksel(x, y);
                if (c.r > 150 && c.g < 100 && c.b < 100) {
                    finish = tochka(x, y);
                    finish_najden = true;
                    stena[y][x] = false;
                    break;
                }
            }
            if (finish_najden) break;
        }
    }

    if (!start_najden) {
        std::cout << "зелёный вход так и не найден" << std::endl;
        start = tochka(10, 10);
    }
    if (!finish_najden) {
        std::cout << "красный выход так и не найден" << std::endl;
        finish = tochka(w - 10, h - 10);
    }

    std::cout << "старт: (" << start.x << ", " << start.y << ")" << std::endl;
    std::cout << "финиш: (" << finish.x << ", " << finish.y << ")" << std::endl;
}

std::vector<tochka> labirint::najti_put() {
    std::vector<std::vector<int>> dist(h, std::vector<int>(w, -1));
    
    std::queue<tochka> q;
    q.push(start);
    dist[start.y][start.x] = 0;

    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    bool found = false;

    while (!q.empty()) {
        tochka cur = q.front();
        q.pop();

        if (cur == finish) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx >= 0 && nx < w && ny >= 0 && ny < h && 
                !stena[ny][nx] && dist[ny][nx] == -1) {
                dist[ny][nx] = dist[cur.y][cur.x] + 1;
                q.push(tochka(nx, ny));
            }
        }
    }

    std::vector<tochka> put;
    if (!found) return put;

    tochka cur = finish;
    put.push_back(cur);

    while (!(cur == start)) {
        for (int i = 0; i < 4; ++i) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx >= 0 && nx < w && ny >= 0 && ny < h &&
                dist[ny][nx] != -1 && dist[ny][nx] == dist[cur.y][cur.x] - 1) {
                cur = tochka(nx, ny);
                put.push_back(cur);
                break;
            }
        }
    }

    std::reverse(put.begin(), put.end());
    return put;
}

void labirint::narisovat_put(kartinka& img, const std::vector<tochka>& put) const {
    cvet siniy(0, 0, 255); // синий цвет
    
    // проходим по всем точкам пути
    for (const auto& p : put) {
        // не красим старт и финиш
        if (!(p == start) && !(p == finish)) {
            // красим саму точку
            img.set_piksel(p.x, p.y, siniy);
            
            // делаем линию потолще
            // ну и проверяем, чтоб не выйти за границы картинки
            
            // вверх
            if (p.y - 1 >= 0) {
                img.set_piksel(p.x, p.y - 1, siniy);
            }
            // вниз
            if (p.y + 1 < img.get_h()) {
                img.set_piksel(p.x, p.y + 1, siniy);
            }
            // влево
            if (p.x - 1 >= 0) {
                img.set_piksel(p.x - 1, p.y, siniy);
            }
            // вправо
            if (p.x + 1 < img.get_w()) {
                img.set_piksel(p.x + 1, p.y, siniy);
            }
        }
    }
}