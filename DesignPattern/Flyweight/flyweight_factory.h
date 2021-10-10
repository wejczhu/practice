#ifndef FLYWEIGHT_FACTORY_H
#define FLYWEIGHT_FACTORY_H

#include "concrete_flyweight.h"
#include <map>

class PlayerFactory
{
public:
    static IPlayer* getPlayer(std::string type)
    {
        IPlayer *p = NULL;
        if(m_map.find(type) != m_map.end())
        {
            p = m_map[type];
        }
        else
        {
            if(type == "T")
            {
                std::cout << "Terrorist Created" << std::endl;
                p = new Terrorist(); 
            }
            else if(type == "CT")
            {
                std::cout << "Counter Terrorist Created" << std::endl;
                p = new CounterTerrorist();
            }
            else
            {
                std::cout << "Undreachable code!" << std::endl;
            }

            m_map.insert(std::make_pair(type, p));
        }

        return p;
    }

private:
    static std::map<std::string, IPlayer*> m_map;
};


#endif