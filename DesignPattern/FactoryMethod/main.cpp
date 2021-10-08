#include "concrete_factory.h"
#include "product.h"
#include <iostream>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) {if(p) {delete(p); (p)=NULL;}}
#endif

int main()
{
    AFactory *pFactory = new BenzFactory();
    ICar *pCar = pFactory->CreateCar();
    cout << "Benz factory : " << pCar->Name() << std::endl;

    SAFE_DELETE(pCar);
    SAFE_DELETE(pFactory);

    AFactory *pFactory = new BmwFactory();
    ICar *pCar = pFactory->CreateCar();
    cout << "Bmw factory : " << pCar->Name() << std::endl;

    SAFE_DELETE(pCar);
    SAFE_DELETE(pFactory);

    AFactory *pFactory = new AudiFactory();
    ICar *pCar = pFactory->CreateCar();
    cout << "Audi factory : " << pCar->Name() << std::endl;

    SAFE_DELETE(pCar);
    SAFE_DELETE(pFactory);

    getchar();

    return 0;
}