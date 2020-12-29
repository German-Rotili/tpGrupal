#ifndef __SERVER_WEAPON_H__
#define __SERVER_WEAPON_H__
#include "server_Map.h"


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