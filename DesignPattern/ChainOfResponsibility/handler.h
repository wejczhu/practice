#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>

class IHandler
{
public:
    virtual ~IHandler() {}
    void SetSuccessor(IHandler *successor)
    {
        m_pSuccessor = successor;
    }
    virtual void HandlerRequest(int days) = 0;
protected:
    IHandler *m_pSuccessor = nullptr;
};

#endif
