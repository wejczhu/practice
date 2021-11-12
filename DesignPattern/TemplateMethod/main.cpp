#include "concrete_class.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) {if(p){delete(p); (p)=nullptr;}}
#endif

int main()
{
    Company *alibaba = new Alibaba();
    alibaba->Recruit();

    Company *tencent = new Tencent();
    tencent->Recruit();

    SAFE_DELETE(tencent);
    SAFE_DELETE(alibaba);

    getchar();

    return 0;
}