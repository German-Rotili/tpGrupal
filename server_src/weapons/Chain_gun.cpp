#include "../server_Config.h"
#include "Chain_gun.h"
#include "../Constants.h"

Chain_gun::Chain_gun(Map &map, Config &config) {
    this->max_damage = config.get_max_damage(CHAIN_GUN);
    this->max_spread = config.get_max_spread(CHAIN_GUN);
    this->map = map;    
}
