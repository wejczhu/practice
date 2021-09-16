#ifndef _SUDOKU_COMMAND_H_
#define _SUDOKU_COMMAND_H_

#include <memory>
#include "common.h"

class SceneC;
class CommandC
{
public:
    CommandC(SceneC* pOwner);
    CommandC(SceneC* pOwner, const point_t &point, int preValue, int cruValue);
    CommandC(const CommandC &);
    ~CommandC();

    bool Execute(int nInputValue);
    void Undo();
    point_t GetPoint() {return mPoint;}
    int GetPreValue() {return mPreValue;}
    int GetCurValue() {return mCurValue;}
    void setPoint(const point_t & point) { mPoint = point; }
    void SetPrevalue(int preValue) { mPreValue = preValue;}
    void SetCurValue(int curValue) { mCurValue = curValue; }

private:
    SceneC* mOwner;
    point_t mPoint;
    int mPreValue;
    int mCurValue;
};

#endif
