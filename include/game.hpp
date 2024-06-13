#pragma once

#include <memory>
#include <iostream>
#include <list>
#include <thread>
#include <assert.h>

#include "board.hpp"
#include "ui_fwd.hpp"

#include <fstream>

class Game {
private:
    std::shared_ptr<Board> board;
    int steps = 0;
    bool game_over = false;
    bool win = false;
    uint8_t last_amount_mine;

    std::list<Position> marked_mines; 
    std::list<Position> marked_miss; 

    void _reveal(Position pos, std::shared_ptr<Board> board);

public:
    Game(uint8_t bd_size_x = 50, uint8_t bd_size_y = 20);

    std::pair<uint8_t, uint8_t> BoardSize() const;

    std::shared_ptr<Board> GetBoard();

    BoardValue GetValue(uint8_t x, uint8_t y);

    std::string GetHeaderText() const;

    bool MouseEvent(Position pos, ui::Mouse& mouse);

    void FillBoardRandomMine(uint8_t amount);

    bool& IsGameOver();
    bool& IsWin();

    void Restart();
};
