#include "../ServerConfigHandler.h"
#include "Chain_gun.h"
#include "Weapon.h"
#include "../Constants.h"
#include "../Map.h"
#include "../../common_src/Timer.h"
#include <random>

Chain_gun::Chain_gun(Map *map, ServerConfigHandler *config, Inventory *inventory) : Weapon{map, config, inventory}  {
  this->map = map;
  weaponStats_t stats = this->config->getWeaponStats(MINIGUN);
  this->max_damage = stats.max_damage;
  this->max_spread = stats.max_spread;
  this->ammo_cost = stats.ammo_cost;
  this->cooldown = stats.cooldown;
  this->stability_reset = stats.stability_reset;
  this->max_acurate_range = stats.max_acurate_range;
}

void Chain_gun::attack() {
  if (!this->is_in_cooldown() && this->has_ammo()) {
    float angle = this->get_shot_angle();
    this->fire(angle);
    this->last_shot_timer.start();
    this->inventory->spend_ammo(this->ammo_cost);
  }
}
float Chain_gun::get_shot_angle() {
  float angle = this->inventory->get_player()->get_direction();
  // cuando mas tiempo paso desde el ultimo disparo menos afecta el spred. hasta
  // el tiempo de reset. REVISAR PARA QUE AUMENTE CON EL NUMERO DE DISPAROS.
  float angle_variation = std::rand() % this->max_spread;
  

  return angle + angle_variation;
}
