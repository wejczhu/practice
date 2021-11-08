#ifndef CONCRETE_STRATEGY_H
#define CONCRETE_STRATEGY_H

#include "strategy.h"
#include <iostream>

class Bike : public ITransport
{
public:
    void Run() override
    {
        std::cout << "By bike" << std::endl;
    }
};

class Car : public ITransport
{
public:
    void Run() override
    {
        std::cout << "By car" << std::endl;
    }
};
class Train : public ITransport
{
public:
    void Run() override
    {
        std::cout << "By train" << std::endl;
    }
};

#endif // CONCRETE_STRATEGY_H
