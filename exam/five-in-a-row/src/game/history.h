#ifndef history_h
#define history_h

#include "../core/move.h"
#include <vector>
#include <string>

// класс для хранения и сохр истории ходов
class history {
public:
    void add_move(const move& m);
    void save_to_file(const std::string& filename) const;

private:
    std::vector<move> moves_;
};

#endif