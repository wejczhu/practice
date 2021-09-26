#include "scene.h"
#include "command.h"

CommandC::CommandC(SceneC* pOwner) : mOwner(pOwner)
{

}

CommandC::CommandC(SceneC* Owner, const point_t &point, int preValue, int curValue)
: mOwner(Owner)
, mPoint(point)
, mPreValue(preValue)
, mCurValue(curValue)
{}

CommandC::CommandC(const CommandC &rhs)
: mOwner(rhd.mOwner)
, mPoint(rhs.mPoint)
, mPreValue(rhs.mPreValue)
, mCurValue(rhs,mCurValue)
{}

command::~CommandC() {}


bool CommandC::Execute(int nInputValue)
{
    if(!mOwner)
    {
        return false;
    }

    mPoint = mOwner->GetCurPoint();
    return mOwner->SetCurvalue(nInputValue, mPreValue);
}


void CommandC::Undo()
{
    if(mOwner)
    {
        mOwner->SetPointValue(mPoint, mPreValue);
    }

    return;
}