#ifndef ADAPTER_H
#define ADAPTER_H

#include "target.h"
#include "adaptee.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) {if(p) {delete(p); (p)=NULL;}}
#endif

class PowerAdapter : public IRussiaSocket
{
public:
    PowerAdapter() : m_pCharger(new OwnCharger()) {}
    ~PowerAdapter()
    {
        SAFE_DELETE(m_pCharger);
    }

    void Charge()
    {
        m_pCharger->chargewithFeetFlat();
    }
private:
    OwnCharger *m_pCharger;
};

#endif
