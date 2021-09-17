#include <iostream>
#include <sstream>
#include <string>
#include "common.h"
#include "utility.inl"

int inputDifficulty()
{
    cls();
    std::string cmd;
    int need_erase_grids = 0;
    while(true)
    {
        std::cout <<" set difficulty: 1 easy, 2 common, 3 hard" << std::endl;
        std::cin >> cmd;

        try
        {
            Difficulty difficulty = static_cast<Difficulty>(std::stoi(cmd));
            switch(difficulty)
            {
                case Difficulty::EASY:
                    need_erase_grids = 20;
                    break;
                case Difficulty::NORMAL:
                    need_erase_grids = 35;
                    break;
                case Difficulty::HARD:
                    need_erase_grids = 50;
                    break;
            }
        }
        catch(...)
        {
            need_erase_grids = 0;
        }

        if(need_erase_grids > 0)
        {
            break;
        }

        std::cout << "input error" << std::endl;
    }

    return need_erase_grids;    
}