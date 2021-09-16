#ifndef _SUDOKU_COLOR_H_
#define _SUDOKU_COLOR_H_

#include <iostream>

namespace Color
{
enum Code
{
    BOLD = 1,
    RESET = 0,
    BG_BLUE = 44,
    BG_DEFAULT = 49,
    BG_GREEN = 42,
    GB_RED = 41,
    FG_BLACK = 30,
    FG_CYAN = 36,
    FG_DARK_GRAY = 90,
    FG_DEFAULT = 39,
    FG_GREEN = 32,
    FG_LIGHT_BLUE = 94,
    FG_LIGHT_CYAN = 96,
    FG_LIGHT_GRAY = 37,
    FG_LIGHT_GREEN = 92,
    FG_LIGHT_MAGENTA = 95,
    FG_LIGHT_RED = 91,
    FG_LIGHT_YELLOG = 93,
    FG_RED = 31,
    FG_WHITE = 97,
    FG_YELLOW = 33
};

class ModifierC
{
    Code code;
public:
    ModifierC(Code pCode) : code(pCode) {}
    friend std::ostream &
    operator<<(std::ostream &os, const ModifierC &mod)
    {
        return os << "\033[" << mod.code << "m";
    }
};

}

#endif