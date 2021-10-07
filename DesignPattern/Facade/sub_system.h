#ifndef SUB_SYSTEM_H
#define SUB_SYSTEM_H

#include <iostream>
#include <string>
#include <windows.h>

const std::string c_stateToStrCourier[] = ""
const std::string
const std::string
const int c_nMsec = 300;

class OrderTeam
{
public:
    void submitRequest()
    {
        m_nState = 0;
    }

    bool checkStatus()
    {
        std::cout << "order team - current state:" << endl;

        Sleep(c_nMsec);
        m_nState++;

        return (m_nState == Complete);
    }
};


class Vendor
{
public:
    void submitReqeust()
    {
        m_nState = 0;
    }

    bool checkStatus()
    {
        std::cout << "vendor - state: " << c_stateToStrVendor[m_nState] << std::endl;

        Sleep(c_nMsec);
        m_nState++;

        return (m_nState == Complete);
    }
}



class Courier
{
public:
    void submitRequest()
    {
        m_nState = 0;
    }

    bool checkStatus()
    {
        std::cout << "courier - current state: " << c_stateToStrCourier[m_nState] << std::endl;

        Sleep(c_nMsec);
        m_nState++;

        return (m_nState == Complete);
    }

private:
    enum States
    {
        Received,
        VerifyReachbility,
        AssignPerson,
        DispatchPackage,
        GetDeliverConfirmation,
        Complete
    };

    int m_nState;
};

#endif