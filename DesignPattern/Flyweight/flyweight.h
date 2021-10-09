#ifndef FLYWEIGHT_H
#define FLYWEIGHT_H

#include <iostream>
#include <string>

class IPlayer
{
public:
    virtual ~Iplayer() {}

    virtual void assignWeapon(std::string weapon) = 0;

    virtual void mission() = 0;

protected:
    std::string m_task;
    std::string m_weapon;

};

#endif