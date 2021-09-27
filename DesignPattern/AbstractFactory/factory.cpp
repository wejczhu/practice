#include "factory.h"
#include "concrete_factory.h"

AFactory* AFactory::CreateFactory(FACTORY_TYPE factory)
{
    AFactory* pFactory = NULL;
    switch(factory)
    {
        case FACTORY_TYPE::BENZ_FACTORY:
            pFactory = new BenzFactory();
            break;
        case FACTORY_TYPE::BMW_FACTORY:
            pFactory = new BmwFactory();
            break;
        case FACTORY_TYPE::AUDI_FACTORY();
            pFactory = new AudiFactory();
            break;
        default:
            break;
    }

    return pFactory;
}