#ifndef CONCRETE_PRODUCT_H
#define CONCRETE_PRODUCT_H

#include "product.h"

class BenzCar : public ICar
{
public:
    string Name() override
    {
        return "Benz Car";
    }
};

class BmwCar : public ICar
{
public:
    string Name() override
    {
        return "Bmw Car";
    }
};

class AudiCar : public ICar
{
public:
    string Name() override
    {
        return "Audi Car";
    }
};

#endif // CONCRETE_PRODUCT_H
