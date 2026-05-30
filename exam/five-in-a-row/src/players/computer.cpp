#include "computer.h"
#include <ctime>
#include <algorithm>

// возвращает лучший ход для заданного символа
move computer::get_best_move(const board& b, char player_symbol, int move_number) const {
    int best_row = -1, best_col = -1;
    int best_score = -1;

    for (int i = 0; i < board::SIZE; ++i) {
        for (int j = 0; j < board::SIZE; ++j) {
            if (!b.is_valid(i, j)) continue;
            int score = evaluate_cell(b, i, j, player_symbol);
            if (score > best_score) {
                best_score = score;
                best_row = i;
                best_col = j;
            }
        }
    }

    //  если поле полностью заполнено (таакого не случится, но на всякий случай)
    if (best_row == -1 || best_col == -1) {
        return move(move_number, player_symbol, -1, -1, get_current_time(), false);
    }

    return move(move_number, player_symbol, best_row, best_col, get_current_time(), false);
}

// возвр подсказку, пометил как hint
move computer::get_hint(const board& b, char player_symbol, int move_number) const {
    move m = get_best_move(b, player_symbol, move_number);
    m.is_hint = true;
    return m;
}

// сумма баллов за потенциальные ряды (свои и чужие)
int computer::evaluate_cell(const board& b, int row, int col, char player_symbol) const {
    char opponent = (player_symbol == 'X') ? 'O' : 'X';
    int total = 0;

    const int dirs[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}};
    for (const auto& dir : dirs) {
        // подсчет своих цепей
        int my_count = 1;
        for (int step = 1; step < 5; ++step) {
            int nr = row + dir[0] * step;
            int nc = col + dir[1] * step;
            if (nr < 0 || nr >= board::SIZE || nc < 0 || nc >= board::SIZE) break;
            char s = b.get_symbol_at(nr, nc);
            if (s == player_symbol) ++my_count;
            else if (s == '_') break;
            else break;
        }
        for (int step = 1; step < 5; ++step) {
            int nr = row - dir[0] * step;
            int nc = col - dir[1] * step;
            if (nr < 0 || nr >= board::SIZE || nc < 0 || nc >= board::SIZE) break;
            char s = b.get_symbol_at(nr, nc);
            if (s == player_symbol) ++my_count;
            else if (s == '_') break;
            else break;
        }

        // подсчет чужих цепей, ну угроз оппонента
        int opp_count = 1;
        for (int step = 1; step < 5; ++step) {
            int nr = row + dir[0] * step;
            int nc = col + dir[1] * step;
            if (nr < 0 || nr >= board::SIZE || nc < 0 || nc >= board::SIZE) break;
            char s = b.get_symbol_at(nr, nc);
            if (s == opponent) ++opp_count;
            else if (s == '_') break;
            else break;
        }
        for (int step = 1; step < 5; ++step) {
            int nr = row - dir[0] * step;
            int nc = col - dir[1] * step;
            if (nr < 0 || nr >= board::SIZE || nc < 0 || nc >= board::SIZE) break;
            char s = b.get_symbol_at(nr, nc);
            if (s == opponent) ++opp_count;
            else if (s == '_') break;
            else break;
        }

        // +баллы
        if (my_count >= 5) total += 10000;
        else if (my_count == 4) total += 1000;
        else if (my_count == 3) total += 100;
        else if (my_count == 2) total += 10;

        if (opp_count >= 5) total += 5000;
        else if (opp_count == 4) total += 500;
        else if (opp_count == 3) total += 50;
    }
    return total;
}

// а это тоже для сохранения временной метки в истории ходов, но компьютера
std::string computer::get_current_time() const {
    time_t now = time(nullptr);
    char buf[80];
    struct tm* t = localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);
    return std::string(buf);
}