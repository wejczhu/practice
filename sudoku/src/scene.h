#ifndef _SUDOKU_SCENE_H_
#define _SUDOKU_SCENE_H_

#include <iostream>
#include <vector>
#include "common.h"
#include "block.h"
#include "command.h"

class SceneC
{
public:
    SceneC(int index = 3);
    virtual ~SceneC();

    void Generate();
    void Show() const;

    bool SetCurValue(const int nCurValue, int& nLastValue);
    bool SetPointValue(const point_t&, const int);
    point_t GetCurPoint();

    void EraseRandomGrids(const int count);
    void IsComplete();

    void Play();
    void Save(const char* filename);
    void Load(const char* filename);

private:
    void Init();
    void SetValue(const int);
    void SetValue(const point_t&, const int);
    void PrintUnderline(int line_no = -1) const;

private:
    int mMaxColumn;
    point_t mCurPoint;
    BlockC mColumnBlock[9];
    BlockC mRowBlock[9];
    BlockC mXYBlock[3][3];
    point_value_t mMap[81];

    std::vector<CommandC> mCommand;

};

#endif
