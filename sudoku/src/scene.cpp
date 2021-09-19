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

void


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