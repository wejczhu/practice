#include "refined_abstraction.h"
#include "concrete_implementor.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) {if(p) {delete p; p = nullptr;}}
#endif

int main()
{
    IEquipment *light = new Light();
    IEquipment *fan = new Fan();

    ISwitch *pullChain = new PullchainSwitch(light);
    ISwitch *twoPositon = new TwoPositionSwitch(fan);

    pullChain->On();
    pullChain->Off();

    twoPositon->On();
    twoPositon->Off();

    SAFE_DELETE(twoPositon);
    SAFE_DELETE(pullChain);
    SAFE_DELETE(fan);
    SAFE_DELETE(light);

    getchar();
    return 0;
}