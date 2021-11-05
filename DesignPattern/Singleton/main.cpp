#include <singleton.h>
#include <iostream>

using namespace std;

Singleton::GC Singleton::GC::gc;

int main()
{
    Singleton::GetInstance();

    return 0;
}