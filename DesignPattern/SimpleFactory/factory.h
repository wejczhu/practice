#ifndef FACTORY_H
#define FACTORY_H

#include "concrete_product.h"

enum class CAR_TYPE
{
    BENZ,
    BMW,
    AUDI
};

class Factory
{
public:
    ICar* CreateCar(CAR_TYPE type)
    {
        ICar* pCar = nullptr;
        switch(type)
        {
            case CAR_TYPE::BENZ:
                pCar = new BenzCar();
                break;
            case CAR_TYPE::BMW:
                pCar = new BmwCar();
                break;
            case CAR_TYPE::AUDI:
                pCar = new AudiCar();
                break;
            default:
                break;
        }
        return pCar;
    }
};

#endif // FACTORY_H
