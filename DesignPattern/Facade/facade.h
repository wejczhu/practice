#ifndef FACADE_H
#define FACADE_H

#include "sub_system.h"

class OnlineShoppingFacade
{
public:
    OnlineShoppingFacade()
    {
        m_nCount = 0;
    }

    int followupNum()
    {
        return m_nCount;
    }

    void submitRequest()
    {
        m_nState = 0;
    }
    
    bool checkStatus()
    {
        switch (m_nState)
        {
            case Received:
                m_nState++;
                m_order.submitRequst
        }
    }



private:
    enum States
    {
        Received,
        SubmittedToOrderTeam,
        SubmittedToVendor,
        SubmittedToCourier
    };

    int m_nState;
    int m_nCount;

    OrderTeam m_order;
    Vendor m_vendor;
    Courier m_courier;
};

#endif