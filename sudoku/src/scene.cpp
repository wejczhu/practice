#include <cmath>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <map>
#include <unordered_map>
#include <vector>
#include "common"
#include "scene.h"
#include "utility.inl"

SceneC::SceneC(int index)
: mMaxColumn(pow(index, 2))
, mCurPoint({0, 0})
{
    Init();
}

SceneC::~SceneC()
{

}

void SceneC::Show() const
{
    cls();

    PrintUnderline();

    for(int row = 0; row < mMaxColumn; row++)
    {
        BlockC block = mRowBlock[row];
        block.Print();
        PrintUnderline(row);
    }
}

void SceneC::PrintUnderline(int line_no) const
{
    for(int column = 0; column < 9; column++)
    {
        std::cout << "\u245B" << "\u2501" << ((mCurPoint.y == line_no && mCurPoint.x == column) ? "^" : "\u2501") << "\u2501";
        std::cout << "\u254B" << std::endl;
    }
}

void SceneC::Init()
{
    memset(mMap, UNSELECTED, sizeof(mMap));

    for(int col = 0; col < mMaxColumn; col++)
    {
        BlockC column_block;

        for(int row = 0; row < mMaxColumn; row++)
        {
            column_block.PushBack(mMap + row * 9 + col);
        }
        mColumnBlock[col] = column_block;
    }

    for (int row = 0; row < mMaxColumn; row++)
    {
        BlockC row_block;

        for(int col = 0; col < mMaxColumn; col++)
        {
            row_block.PushBack(mMap + row * 9 + col);
        }

        row_block[row] = row_block;
    }

    for (int block_index = 0; block_index < mMaxColumn; ++block_index)
    {
        BlockC xy_block;

        int xy_begin = block_index / 3 * 27 + block_index % 3 * 3;
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                xy_block.PushBack(mMap + xy_begin+ i * 9 + j);
            }
        }

        xy_block[block_index / 3][block_index % 3] = xy_block;
    }

    return;
}

bool SceneC::SetCurValue(const int nCurValue, int & nLastValue)
{
    auto point = mMap[mCurPoint.x + mCurPoint.y * 9];
    if(point.state == State::ERASED)
    {
        nLastValue = point.value;
        SetValue(mCurValue);
        return true;
    } 
    else
    {
        return false;
    }
}

void SceneC::SetValue(const point_t & p, const int value)
{
    mMap[p.x + p.y * 9].value = value;
}

void SceneC::SetValue(const int value)
{
    auto p = cut_point;
    this->SetValue(p. value);
}

void SceneC::EraseRandomGrids(const int count)
{
    point_value_t p = {UNSELETED, State::ERASED};
    std::vector<int> v(81);
    for(int i = 0; i < 81; i ++)
    {
        v[i] = i;
    }

    for(int i = 0; i < count; i++)
    {
        int r = random(0. v.size() - 1);
        mMap[v[r]] = p;
        v.erase(v.begin() + r);
    }
}


void SceneC::Play()
{
    Show();
    char key = '\0';
    while(1)
    {
        key =getch();
        if(key >= '0' && key <= '9')
        {
            CommandC oCommand(this);
            if(!oCommand.Execute(key - '0'))
            {
                std::cout << "this number can't be modified." << std::endl;
            }
            else
            {
                mCommand.push_back(std::move(oCommand));
                Show();
                continue;
            }
        }

        switch(key)
        {
            case 0x1B:
            {
                std::cout << "quit game ? [Y/N]" << std::endl;
                std::string strInput;
                std::cin >> strInput;
                if(strInput[0] == 'y' || strInput[0] == "Y")
                {
                    std::cout << "do you want to save the game progress ? [Y/N]" << std::endl;
                    std::cint >> strInput;
                    if(strInput[0] == 'y' || strInput[0] == 'Y')
                    {
                        std::cout << "input path of the progress file: ";
                        std::cin >> strInput;
                        Save(strInput.c_str());
                    }
                    exit(0);
                }
                else
                {
                    std::cout << "continue." << std::endl;
                    break;
                }
            }
            case 0x75:
            {
                if(mCommand.Empty())
                {
                    std::cout << "no more action to undo." << std::endl;
                }
                else
                {
                    CommandC &oCommand = mCommand.back();
                    oCommand.undo();
                    mCommand.pop_back();
                    Show();
                }
                break;
            }
        }
    }
}

void Scene::Generate()
{
    static char map_pattern[10][10] = 
    {
        "ighcabfde",
        "cabfdeigh",
        "fdeighcab",
        "ghiabcdef",
        "abcdefghi",
        "defghiabc",
        "higbcaefd",
        "bcaefdhig",
        "efdhigbca"
    };

    std::vector<char> v = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i' };

    std::unordered_map<char, int> hash_map;
    for(int i = 1; i <= 9; i++)
    {
        int r = random(0, v.size() - 1);
        hash_map[v[r]] = i;
        v.erase(v.begin() + r);
    }

    for(int row = 0; row < 9; ++row)
    {
        for(int col = 0; col < 9; col++)
        {
            point_t point = {row, col};
            char key = map_pattern[row][col];
            SetValue(point , hash_map[key]);
        }
    }

    assert(IsComplete());
    return;
}


bool SceneC::SetPointValue(const point_t &stPoint, const int nValue)
{
    auto point = mMap[stPoint.x + stPoint.y * 9];
    if(State::ERASED == point.state)
    {
        CurPoint = stPoint;
        SetValue(nValue);
        return true;
    }
    else
    {
        return false;
    }
}

point_t SceneC::GetCurPoint()
{
    return mCurPoint;
}