#ifndef __ROCKET_LAUNCHER_H__
#define __ROCKET_LAUNCHER_H__

#include "Weapon.h"
class Map;
class Config;

class  Rocket_launcher : public Weapon{
private:
    Map &map;
    Config &config;

public:

    Rocket_launcher(Map &, Config &);
    ~ Rocket_launcher();
    bool fire();
};
#endif // __ROCKET_LAUNCHER_H__