#ifndef CONCRETE_FLYWEIGHT_H
#define CONCRETE_FLYWEIGHT_H

#include "flyweight.h"

class Terrorist : public IPlayer
{
public:
    Terrorist()
    {
        m_task = "Plant a bomb";
    }

    virtual void assignWeapon(std::string weapon) override
    {
        m_weapon = weapon;
    }

    virtual void mission() override
    {
        std::cout << "Terrorist with weapon " + m_weapon + "," + 
    }
};


#endif
