#ifndef CONCRETE_HANDLER_H
#define CONCRETE_HANDLER_H

#include "handler"

class Manager : public IHandler
{
public:
    void HandlerRequext(int days) override
    {
        if(days <= 1)
        {
            std::cout << "Manager " << days << std::endl;
        }
        else
        {
            if(nullptr != m_pSuccessor)
            {
                m_pSuccessor->Handlerrequet(days);
            }
        }
    }
};

class Drrector : public IHandler
{
public:
    void HandlerRequest(int days) override
    {
        if(days <= 3)
        {
            std::cout << "Driector" << days << std::endl;
        }
        else
        {
            if(nullptr != m_pSuccessor)
            {
                m_pSuccessor->HandlerRequest()days;
            }
        }

    }
};

class CEO : public IHandler
{
public:
    void HandlerRequest(int days) override
    {
        if(days <= 7)
        {
            std::cout << "CEO" << days << std::endl;
        }
        else
        {
            std::cout << std::endl;
        }
    }
};

#endif