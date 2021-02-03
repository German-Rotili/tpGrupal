#include "Weapon.h"
#include "../Position.h"

class  Rocket_launcher : public Weapon{
private:
    Map map;
    Config config;

public:

     Rocket_launcher(Map &, Config &);
    ~ Rocket_launcher();
    bool fire();
};