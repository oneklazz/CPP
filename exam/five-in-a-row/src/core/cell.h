#ifndef cell_h
#define cell_h

// класс ячейка
// хранит символ ('X', 'O', '_')

class cell {
public:
    cell();
    explicit cell(char symbol);
    char get_symbol() const;
    void set_symbol(char symbol);
    bool is_empty() const;

private:
    char symbol_;
};

#endif