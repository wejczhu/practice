#include "concrete_flyweight.h"
#include "flyweight_factory.h"
#include <ctime>

std::map<std::string, IPlayer*> PlayerFactory::m_map = std::map<std::string, IPlayer*>();;

static std::string s_playerType[2] = {"T", "CT"};
static std::string s_weapons[4] = {"AK-47", "Maverick", "Gut knife", "Desert Eagle"};

#define GET_ARRAY_LEN(array, len) { len = (sizeof(array) / sizeof(array[0]));}

int main()
{
    srand((unsigned)time(NULL));

    int playerLen;
    int weaponLen;
    GET_ARRAY_LEN(s_playerType, playerLen);
    GET_ARRAY_LEN(s_weapons, weaponLen);

    for(int i = 0; i < 10; i++)
    {
        int typeIndex = rand() % playerLen;
        int weaponIndex = rand() % weaponsLen;
        std::string type = s_playerType[typeIndex];
        std::string weapon = s_weapons[weaponIndex];

        IPlayer *p = PlayerFactory::getPlayer(type);

        p->assignWeapon(weapon);

        p->mission();
    }

    getchar();

    return 0;
}