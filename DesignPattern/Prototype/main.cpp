#include "concrete_prototype.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) {if(p) {delete (p); p=NULL;}}
#endif

int main()
{
    Monkey *swk = new SunWuKong("qi tian da sheng");

    Monkey *swk1 = swk->Clone();
    Monkey *swk2 = swk->Clone();

    swk1->Play();
    swk2->Play();

    SAFE_DELETE(swk2);
    SAFE_DELETE(swk1);
    SAFE_DELETE(swk);

    getchar();

    return 0;
}