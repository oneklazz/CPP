#include "history.h"
#include <fstream>
#include <iostream>

// + ход в историю
void history::add_move(const move& m) {
    moves_.push_back(m);
}

// сохр историю в txt
void history::save_to_file(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "ошибка: не удалось открыть файл " << filename << "\n";
        return;
    }
    file << "история игры\n";
    file << "=============\n";
    for (const auto& m : moves_) {
        file << m.number << ". "
             << m.symbol << " на ("
             << m.row + 1 << ", " << m.col + 1 << ") "
             << m.time;
        if (m.is_hint) file << " (подсказка)";
        file << "\n";
    }
    file.close();
    std::cout << "история сохранена в " << filename << "\n";
}