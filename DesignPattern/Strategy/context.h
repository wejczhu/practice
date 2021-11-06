#ifndef CONTEXT_H
#define CONTEXT_H

#include "strategy.h"

class Tourists
{
public:
    Tourists(ITransport *transport)
    {
        m_pTransport = transport;
    }

    void Travle()
    {
        if(nullptr != m_pTransport)
        {
            m_pTransport->Run()
        }
    }
private:
    ITransport *m_pTransport = nullptr;
};

#endif // CONTEXT_H
