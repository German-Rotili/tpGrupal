#include "../server_Config.h"
#include "Pistol.h"
#include "../Constants.h"

Pistol::Pistol(Map &map, Config &config) {
    this->max_damage = config.get_max_damage(PISTOL);
    this->max_spread = config.get_max_spread(PISTOL);
    this->map = map;    
}
