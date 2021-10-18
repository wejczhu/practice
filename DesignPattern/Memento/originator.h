#ifndef ORIGINATOR_H
#define ORIGINATOR_H


#include "memento.h"
#include <iostream>
#include <string>

class Life
{
public:
    Life() {}
    ~Life() {}

    void SetDateTime(std::string dt)
    {
        std::cout << "Set date time to " << dt << std::endl;
        m_dateTime = dt;
    }

    std::string GetDateTime()
    {
        return m_dateTime;
    }

    void SetMemento(DateTime* dt)
    {
        if(nullptr != dt)
        {
            m_dateTime = dt->GetDateTime();
        }
    }

    DateTime *CreateMemento()
    {
        return new DateTime(m_dateTime);
    }

private:
    std::string m_dateTime;
};

#endif // ORIGINATOR_H