#include "../server_Config.h"
#include "Knife.h"
#include "../Constants.h"

Knife::Knife(Map &map, Config &config) {
    this->max_damage = config.get_max_damage(KNIFE);
    this->max_spread = config.get_max_spread(KNIFE);
    this->map = map;    
}
