#pragma once

#include "mediator.h"
#include <string>

class IMdeiator;

class IColleague
{
public:
    IColleague(const std::string& name)
    : m_strName(name) {}

    virtual void sendMessage(const IMediator& mediator, const std::string& message) const = 0;

    virtual void receiveMessage(const IColleague* sender, const std::string& message) const = 0;
private:
    sdt::string m_strName;
};