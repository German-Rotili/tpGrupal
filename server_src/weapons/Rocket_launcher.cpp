#include "Rocket_launcher.h"
#include "../Config.h"
#include "../Constants.h"
#include "Rocket.h"
#include "Weapon.h"
#include "../Position.h"
#include "../Map.h"
#include "../Inventory.h"
#include "../Player.h"

Rocket_launcher::Rocket_launcher(Map *map, Config *config, Inventory *inventory) : Weapon{map, config, inventory} {
  this->max_damage = 20; //config->get_max_damage(ROCKET_LAUNCHER);
  this->max_spread = 5; //config->get_max_spread(ROCKET_LAUNCHER);
}

bool Rocket_launcher::fire() {
  if (this->inventory->get_ammo() >= this->ammo_cost && !this->is_in_cooldown()) { //remplazar por has ammo.
    this->map->add_rocket(Rocket(this->map, this->config,
                                this->inventory->get_player()->get_pos_x(),
                                this->inventory->get_player()->get_pos_y(),
                                this->inventory->get_player()->get_direction()));
    this->inventory->spend_ammo(this->ammo_cost);
    this->last_shot_timer.start();
    return true;
  }
  return false;
}
