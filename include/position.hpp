#pragma once

#include <stdint.h>

struct Position {
    int x;
    int y;

    Position(int _x, int _y) : x(_x), y(_y) {}

    bool operator==(const Position& rhs) const {
        if(x != rhs.x) return false;
        return (y == rhs.y);
    }
};


