#include "board.hpp"

bool Board::_validate_position(Position pos) const 
{
    if(pos.x < 0) return false;
    if(pos.y < 0) return false;

    if(pos.x >= _size_x) return false;
    if(pos.y >= _size_y) return false;
    return true;
}

bool Board::_is_mine(Position pos)
{
    if (values[pos.x][pos.y].value == -1) return true;
    return false;
}

bool Board::_increment_hint(Position pos)
{
    if(!_validate_position(pos)) return false;
    if(_is_mine(pos)) return false;
    values[pos.x][pos.y].value++;
    return true;
}

void Board::_add_hints(Position pos)
{
    uint8_t x = pos.x;
    uint8_t y = pos.y;

    _increment_hint(Position{x    , y - 1});
    _increment_hint(Position{x + 1, y - 1});
    _increment_hint(Position{x + 1, y    });
    _increment_hint(Position{x + 1, y + 1});
    _increment_hint(Position{x    , y + 1});
    _increment_hint(Position{x - 1, y + 1});
    _increment_hint(Position{x - 1, y    });
    _increment_hint(Position{x - 1, y - 1});
}

Board::Board(uint8_t x, uint8_t y) : _size_x(x), _size_y(y) 
{
    values.resize(_size_x);
    for(uint8_t i = 0; i < _size_x; i++){
        values[i].resize(_size_y);
        for(uint8_t j = 0; j < _size_y; j++){
            values[i][j] = BoardValue{0, true, false};
        }
    }
}

bool Board::AddMine(Position pos)
{
    if(!_validate_position(pos)) return false;
    if(_is_mine(pos)) return true;

    values[pos.x][pos.y].value = -1;
    _add_hints(pos);
    return true;
}

BoardValue Board::GetValue(Position pos) const 
{
    if(!_validate_position(pos)) return BoardValue{0, true};
    return values[pos.x][pos.y];
}

std::pair<uint8_t, uint8_t> Board::GetSize() const 
{
    return std::make_pair(_size_x, _size_y);
}

void Board::SetValue(Position pos, BoardValue val)
{
    values[pos.x][pos.y] = val;
}

bool Board::IsEmpty(Position pos)
{
    if(!_validate_position(pos))
        return false;

    return values[pos.x][pos.y].value == 0;
}

bool Board::IsHidden(Position pos)
{
    if(!_validate_position(pos))
        return false;

    return values[pos.x][pos.y].hidden;
}

void Board::SetHidden(Position pos, bool hidden)
{
    if(!_validate_position(pos))
        return;

    values[pos.x][pos.y].hidden = hidden;
}

bool Board::IsMine(Position pos)
{
    if(!_validate_position(pos))
        return false;

    return values[pos.x][pos.y].value == -1;
}

void Board::Clear()
{
    for(uint8_t i = 0; i < _size_x; i++){
        for(uint8_t j = 0; j < _size_y; j++){
            values[i][j] = BoardValue{0, true, false};
        }
    }
}

bool Board::ToggleMark(Position pos)
{
    if(!_validate_position(pos))
        return false;

    values[pos.x][pos.y].marked = !values[pos.x][pos.y].marked;
    return true;
}

bool Board::IsMarked(Position pos)
{
    if(!_validate_position(pos))
        return false;

    return values[pos.x][pos.y].marked;
}
