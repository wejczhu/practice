#ifndef CONCRETE_ELEMENT_H
#define CONCRETE_ELEMENT_H

#include "element.h"
#include "visitor.h"
#include <iostream>

class BellTower : public IPlace
{
public:
    virtual void Accept(IVisitor *visitor) override
    {
        std::cout << "Bell Tower is accepting visitor." << std::endl;
        visitor->Visit(this);
    }
};

class TerracottaWarriors : public IPlace
{
public:
    virtual void Accept(IVisitor *visitor) override
    {
        std::cout << "Terracotta Warriors is accepting visitor." << std::endl;
        visitor->Visit(this);
    }
};

#endif // CONCRETE_ELEMENT_H
