#ifndef CONCRETE_FACTORY_H
#define CONCRETE_FACTORy_H
#include "factory.h"
#include "concrete_product.h"

class BenzFactory : public AFactory
{
public:
    ICar* Create()
    {
        return new BenzCar();
    }
};

class BmwFactory : public AFactory
{
public:
    ICar* CreateCar()
    {
        return new BmwCar();
    }
};

class AudiFactory : public AFactory
{
public:
    ICar* CreateCar()
    {
        return new AudiCar();
    }
};

#endif // CONCRETE_FACTORY_H
