#include "originator.h"
#include "care_taker.h"
#include <time.h>
#include <sstream>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) {if(p) {delete (p); (p)=NULL;}}
#endif

int main()
{
    srand((unsigned)time(0));

    Life *life = new Life();
    PandoraBox *box = new PandoraBox(life);

    for (int i = 0; i < 5; i++)
    {
        std::ostringstream buffer;
        buffer << "200" << "/10/01 00:00:00";
        std::string dt = buffer.str();

        life->SetDateTime(dt);
        box->Save();
    }

    for(int i = 0; i < 2; i++)
    {
        box->Undo();
        std::cout << "Current datea time is " << life->GetDateTime() << std::endl;
    }
    SAFE_DELETE(life);
    SAFE_DELETE(box);

    getchar();

    return 0;
}