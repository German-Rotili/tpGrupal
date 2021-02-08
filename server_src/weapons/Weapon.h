#ifndef __SERVER_WEAPON_H__
#define __SERVER_WEAPON_H__
#include "../Map.h"
#include "../Inventory.h"
#include "../../common_src/Timer.h"
class Map;

class Weapon
{
protected:
    Timer last_shot_timer;
    int max_damage;
    int max_spread;
    int ammo_cost;
    int cooldown;
    int stability_reset;
    int max_acurate_range;
    Map &map;
    Inventory &inventory;
    
    void fire(float angle);
    bool is_in_cooldown();
    bool has_ammo();
    virtual float get_shot_angle();

    Weapon();

public:
    virtual bool get_damage(int distance);
    void tick();
    virtual void attack();

};

#endif // __SERVER_WEAPON_H__