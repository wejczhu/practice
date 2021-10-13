#pragma once

#include "colleague.h"
#include <list>

class IColleague;

class IMediator
{
public:
    virtual void registerColleague(IColleague* colleague)
    {
        m_colleagues.emplace_back(colleague);
    }

    virtual void distributeMessage(const IColleague* sender, const std::string& message) const = 0;

private:
    std::list<IColleague*> m_colleagues;
};
