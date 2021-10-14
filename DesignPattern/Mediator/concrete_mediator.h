#ifndef CONCRETE_MEDIATOR_H
#define CONCRETE_MEDIATOR_H

#include "mediator.h"

class ConcreteMediator : public IMdeiator
{
public:
    virtual void distributeMessage(const IColleague* sender, const std::string& message) const override
    {
        for(const IColleague* c : getColleagues())
        {
            if(c != sender)
            {
                c->receiveMessage(sender, message);
            }
        }
    }
};

#endif // CONCRETE_MEDIATOR_H