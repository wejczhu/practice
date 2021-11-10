#ifndef ABSTRACT_CLASS_H
#define ABSTRACT_CLASS_H

#include <iostream>

class Company
{
public:
    virtual ~Company() {}

    void Recruit()
    {
        std::cout << "----------Begin----------" << std::endl;
        CareerTalk();
        ReceiveResume();
        Interview();
        Offer();
        std::cout << "----------End----------" << std::endl;
    }

    void CareerTalk()
    {
        std::cout << "Delivery" << std::endl;
    }

    void ReceiveResume()
    {
        std::cout << "Receive Resume" << std::endl;
    }

    virtual void Interview() = 0;

    virtual void Offer() = 0;
};

#endif // ABSTRACT_CLASS_H
