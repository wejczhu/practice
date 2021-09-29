#ifndef REFINED_ABSTRACTION_H
#define REFINED_ABSTRACTION_H

#include "abstraction.h"
#include <iostream>

class PullchainSwitch : public ISwitch
{
public:
    PullchainSwitch(IEquipment *equipment)
    :ISwitch(equipment) {}

    void On() override
    {
        std::cout << "Switch on the equipment with a pull chain switch" << std::endl;

        if(nullptr != m_pEquipment)
        {
            m_pEquipment->PowerOn();
        }
    }

    void Off() override
    {
        std::cout << "Switch off the equipment with a pull chain switch" << std::endl;

        if(nullptr != m_pEquipment)
        {
            m_pEquipment->PowerOff();
        }
    }
};

class TwoPositionSwitch : public ISwitch
{
public:
    TwoPositionSwitch(IEquipment *equipment)
    : ISwitch(equipment) {}

    void On() override
    {
        std::cout << "Switch on the equipment with a two-position switch" << std::endl;

        if(nullptr != m_pEquipment)
        {
            m_pEquipment->PowerOn();
        }
    }

    void Off() override
    {
        std::cout << "Switch off the equipment with a two-position switch" << std::endl;

        if(nullptr != m_pEquipment)
        {
            m_pEquipment->PowerOff();
        }
    }
}

#endif
