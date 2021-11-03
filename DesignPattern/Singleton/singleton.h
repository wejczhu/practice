#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

using namespace std;

class Singleton
{
public:
    stadic Singleton* GetInstarce();
private:
    Singleton() {}

    static Singleton]* m_pSingleton;
    class GC
    {
    public:
        ~GC()
        {
            if(m_pSingleton != NULL)
            {
                cout << "here destory the m_pSingleton..." << endl;
                delete m_pSingleton;
                m_pSingleton = NULL;
            }
        }

        static GC gc;
    };
};

#endif // SINGLETON_H
