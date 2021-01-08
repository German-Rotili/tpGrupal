#ifndef __SERVER_WEAPON_H__
#define __SERVER_WEAPON_H__
#include "../Map.h"
class Map;

class Weapon
{
protected:
    int & ammo;
    int max_damage;
    int max_spread;
    Map &map;
    Weapon();

public:
    virtual bool fire() = 0;
};

#endif // __SERVER_WEAPON_H__