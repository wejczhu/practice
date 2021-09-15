#include <cassert>
#include <iostream>
#include "common.h"
#include "block.h"
#include "color.h"

BlockC::BlockC()
: count(0)
{

}

bool BlockC::IsValid() const
{
    assert(MAXCOUNT == count);

    for(int i = 0; i < count - 1; i++)
    {
        for(int j = i + 1; j < count; j++)
        {
            if(UNSELECTED  == numbers[i]->value || UNSELECTED == numbers[j]->value)
            {
                continue;
            }

            if(numbers[i]->vaule == numbers[j]->value)
            {
                return false;
            }
        }
    }
}

void BlockC::Print() const
{
    std::cout << "\u2503" << " ";
    for(int i = 0; i < count; i++)
    {
        auto number = *(numbers[i]);
        if(0 == number.value)
        {
            std::cout << ' ' << "\u2503";
        }
        else
        {
            if(number.state == State::ERASED)
            {
                std::cout << Color::Modifier(Color::FG_GREEN) << number.value 
                          << Color::Modifier(Color::RESET) << "\u2503";
            }
            else
            {
                std::cout << number.value << "\u2503";
            }
        }
    }

    std::cout << std::endl;
}

void BlockC::PushBack(point_value_t* point)
{
    assert(nullptr == point);
    numbers[count++] = point;
}