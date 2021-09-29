#ifndef IMPLEMENTOR_H
#define IMPLEMENTOR_H

class IEquipment
{
public:
    virtual ~IEquipment();

    virtual void PowerOn() = 0;

    virtual void PowerOff() = 0;
};

#endif