#include "Rocket_launcher.h"
#include "Rocket.h"
#include "../ServerConfigHandler.h"
#include "../Constants.h"
#include "../Inventory.h"
#include "../Map.h"
#include "../Player.h"
#include "../Position.h"
#include "Weapon.h"

Rocket_launcher::Rocket_launcher(Map *map, ServerConfigHandler *config, Inventory *inventory)
    : Weapon{map, config, inventory} {
  this->max_damage = 20; // config->get_max_damage(ROCKET_LAUNCHER);
  this->max_spread = 5;  // config->get_max_spread(ROCKET_LAUNCHER);
  weaponStats_t stats = this->config->getWeaponStats(ROCKETLAUNCHER);
  this->max_damage = stats.max_damage;
  this->max_spread = stats.max_spread;
  this->ammo_cost = stats.ammo_cost;
  this->cooldown = stats.cooldown;
  this->stability_reset = stats.stability_reset;
  this->max_acurate_range = stats.max_acurate_range;
}

bool Rocket_launcher::fire() {
  if (this->inventory->get_ammo() >= this->ammo_cost &&
      !this->is_in_cooldown()) { // remplazar por has ammo.

    this->map->add_rocket(this->inventory->get_player()->get_pos_x(),
                          this->inventory->get_player()->get_pos_y(),
                          this->inventory->get_player()->get_direction(),
                          this->inventory->get_player());
    this->inventory->spend_ammo(this->ammo_cost);
    this->last_shot_timer.start();
    this->map->add_action(this->inventory->get_player()->get_id(),
                          this->inventory->get_current_weapon_id(),
                          this->inventory->get_player()->get_pos_x(),
                          this->inventory->get_player()->get_pos_y());

    return true;
  }
  return false;
}

void Rocket_launcher::attack() { this->fire(); }
