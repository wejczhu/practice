#ifndef ABSTRACTION_H
#define ABSTRACTION_H

#include "implementor.h"

class ISwitch
{
public:
    ISwitch(IEquipment *equipment)
    {
        m_pEquipment = equipment;
    }

    virtual ~ISwitch() {}

    virtual void On() = 0;

    virtual void Off() = 0;

protected:
    IEquipment *m_pEquipment = nullptr;
};

#endif