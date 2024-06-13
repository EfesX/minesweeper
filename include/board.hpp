#pragma once

#include <vector>
#include <stdint.h>

#include "position.hpp"

struct BoardValue {
    int  value;
    bool hidden;
    bool marked;
};

class Board {
private:
    std::vector<std::vector<BoardValue>> values;

    uint8_t _size_x;
    uint8_t _size_y;

    bool _validate_position(Position pos) const;
    bool _is_mine(Position pos);
    bool _increment_hint(Position pos);
    void _add_hints(Position pos);

public:
    Board(uint8_t x, uint8_t y);

    bool AddMine(Position pos);

    void SetValue(Position pos, BoardValue val);
    void SetHidden(Position pos, bool hidden);
    bool ToggleMark(Position pos);

    BoardValue GetValue(Position pos) const;
    std::pair<uint8_t, uint8_t> GetSize() const;
    
    bool IsEmpty(Position pos);
    bool IsHidden(Position pos);
    bool IsMine(Position pos);
    bool IsMarked(Position pos);
    
    void Clear();
};
