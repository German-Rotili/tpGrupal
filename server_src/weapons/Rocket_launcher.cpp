#include "../Config.h"
#include "Rocket_launcher.h"
#include "../Constants.h"

Rocket_launcher::Rocket_launcher(Map &map, Config &config) {
    this->max_damage = config.get_max_damage(ROCKET_LAUNCHER);
    this->max_spread = config.get_max_spread(ROCKET_LAUNCHER);
    this->map = map;
}

bool Rocket_launcher::fire(){
    this->map.add_rocket();
    
}
