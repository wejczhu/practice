#ifndef FACTORY_H
#define FACTORY_H

#include "product.h"

class AFactory
{
public:
    virtual ICar* CreateCar() = 0;
};

#endif
