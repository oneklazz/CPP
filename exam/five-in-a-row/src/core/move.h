#ifndef move_h
#define move_h

#include <string>

// структура хода для хистори
struct move {
    int number;          // номер хода
    char symbol;         // 'X' или 'O'
    int row;             // строка
    int col;             // столбец
    std::string time;    // временная метка
    bool is_hint;        // true, если ход был подсказкой

    // коннструктор для удобства
    move(int num, char sym, int r, int c, const std::string& t, bool hint = false)
        : number(num), symbol(sym), row(r), col(c), time(t), is_hint(hint) {}
};

#endif