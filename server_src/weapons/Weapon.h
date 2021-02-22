#ifndef __SERVER_WEAPON_H__
#define __SERVER_WEAPON_H__

#include "../Player.h"
#include "../../common_src/Timer.h"
#include "../Inventory.h"
#include "../Map.h"

class Weapon
{
protected:
    Timer last_shot_timer;
    int max_damage = 5;
    int max_spread = 5;
    int ammo_cost = 1;
    int cooldown = 200;
    int stability_reset = 300;
    int max_acurate_range = 5;
    Map *map;
    Inventory *inventory;
    ServerConfigHandler *config;
    
    void fire(float angle);
    bool is_in_cooldown();
    bool has_ammo();
    virtual float get_shot_angle();
    Weapon(Map *, ServerConfigHandler *, Inventory *);


public:
    virtual int get_damage(int distance);
    virtual void tick(){};
    virtual void attack(){};

};

#endif // __SERVER_WEAPON_H__