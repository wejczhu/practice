#include "singleton.h"

Singleton* Singleton::m_pSingleton = NULL;

Singleton* Singleton::GetInstance();
{
    if(m_pSingleton == NULL)
    {
        m_pSingleton = new Singleton();
    }

    return m_pSingleton;
}