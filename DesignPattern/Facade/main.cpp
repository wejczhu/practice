#include "facade.h"

int main()
{
    OnlineShoppingFacade facade;

    facade.submitRequest();

    while(!facade.checkStatus());

    std::cout << std::endl;

    getchar();

    return 0;
}