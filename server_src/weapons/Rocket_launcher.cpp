#include "Rocket_launcher.h"
#include "../Config.h"
#include "../Constants.h"
#include "Rocket.h"
#include "Weapon.h"
#include "../Position.h"
#include "../Map.h"
#include "../Inventory.h"
#include "../Player.h"

Rocket_launcher::Rocket_launcher(Map *map, Config *config) : map{map}{
  this->max_damage = config.get_max_damage(ROCKET_LAUNCHER);
  this->max_spread = config.get_max_spread(ROCKET_LAUNCHER);
  this->map = map;
}

bool Rocket_launcher::fire() {
  if (this->inventory.get_ammo() >= this->ammo_cost && !this->is_in_cooldown()) { //remplazar por has ammo.
    this->map->add_rocket(Rocket(this->map-> this->config,
                                this->inventory.get_player().get_pos_x(),
                                this->inventory.get_player().get_pos_y(),
                                this->inventory.get_player().get_direction()));
    this->inventory.spend_ammo(this->ammo_cost);
    this->last_shot_timer.start();
    return true;
  }
  return false;
}
