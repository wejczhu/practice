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