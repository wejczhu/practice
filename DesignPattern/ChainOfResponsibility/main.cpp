#include "concrete_handler.h"

#ifndef SAFE_DELETE
#define  SAFE_DELATE(p) {if(p) {delete p; (p) = nullptr;} }
#endif

int main()
{
    IHandler *manager = new Manager();
    IHandler *director = new Director();
    IHandler *ceo = new CEO();

    manager->SetSuccessor(director);
    director->SetSuccessor(ceo);

    manager->HandlerRequset(1);
    manager->HandlerRequset(2);
    manager->HandlerRequset(5);
    manager->HandlerRequset(10);

    SAFE_DELATE(manager);
    SAFE_DELATE(director);
    SAFE_DELATE(ceo);

    getchar();
    return 0;
}