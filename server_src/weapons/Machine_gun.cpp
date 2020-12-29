#include "../server_Config.h"
#include "Machine_gun.h"
#include "../Constants.h"

Machine_gun::Machine_gun(Map &map, Config &config) {
    this->max_damage = config.get_max_damage(MACHINE_GUN);
    this->max_spread = config.get_max_spread(MACHINE_GUN);
    this->map = map;    
}
