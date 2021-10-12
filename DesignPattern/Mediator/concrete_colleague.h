#ifndef CONCRETE_COLLEAGUE_H
#define CONCRETE_COLLEAGUE_H

#include "colleague.h"
#include <iostream>

class ConcreteColleague : public IColleague
{
public:
    using IColleage::IColleague;

    virtual void sendMessage(const IMdeiator mediator, const std::string& message) const override
    {
        mediator.distributeMessage(this, message);
    }
private:
    virtual void receiveMessage(const IColleague* sender, const std::string& message) const override
    {
        std::cout << getName() << "received the message from" 
        << sender->getName() << ": " << message << std::endl;
    }
};

#endif