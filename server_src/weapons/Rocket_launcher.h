#include "Weapon.h"
#include "../Position.h"

class  Rocket_launcher : public Weapon{
private:
    /* data */
public:

     Rocket_launcher(Map &, Config &);
    ~ Rocket_launcher();
    bool fire();
};