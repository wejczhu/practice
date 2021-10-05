#ifndef DECORATOR_H
#define DECORATOR_H

#include "component.h"

class CondimentDecorator : public IBeverage
{
public:
    CondimentDecorator(IBeverage *beverage) : m_pBeverage(beverage) {}

    string Name()
    {
        return m_pBeverage->Name();
    }

    double cost()
    {
        return m_pBeverage->Cost();
    }

protected:
    IBeverage* m_pBeverage;
};

#endif // DECORAT0R_H
