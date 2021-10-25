#ifndef CONCRETE_PROTOTYPE_H
#define CONCRETE_PROTOTYPE_H

#include "prototype.h"
#include <iostream>
#include <string>

using namespace std;

class SunWuKong : public Monkey
{
public:
    SunWuKong(string name)
    {
        m_strName = name;
    }
    ~SunWuKong(){}

    SunWuKong(const SunWuKong &other)
    {
        m_strName = other.m_strName;
    }

    Monkey* Clone()
    {
        return new SunWuKong(*this);
    }

    void Play()
    {
        cout << m_strName << " Play Golden-Hoop-Stick " << endl;
    }

private:
    string m_strName;
};

#endif // CONCRETE_PROTOTYPE_H
