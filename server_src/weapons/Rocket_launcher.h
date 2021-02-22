#ifndef __ROCKET_LAUNCHER_H__
#define __ROCKET_LAUNCHER_H__

#include "Weapon.h"
class Map;
class Config;


class  Rocket_launcher : public Weapon{
private:


public:

    Rocket_launcher(Map *, Config *, Inventory *);
    bool fire();
    void attack() override;

};
#endif // __ROCKET_LAUNCHER_H__