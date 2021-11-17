#ifndef OBJECT_STRUCTURE_H
#define OBJECT_STRUCTURE_H

#include "element.h"
#include <list>

class City
{
public:
    void Attach(IPlace *place)
    {
        m_places.push_back(place);
    }

    void Detach(IPlace *place)
    {
        m_places.remove(place);
    }

    void Accept(IVisitor *visitor)
    {
        for(std::list<IPlace*>::iterator it = m_places.begin(); it != m_places.end(); ++it)
        {
            (*it)->Accept(visitor);
        }
    }

private:
    std::list<IPlace *> m_places;
};

#endif // OBJECT_STRUCTURE_H
