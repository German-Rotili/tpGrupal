#include "../Config.h"
#include "Chain_gun.h"
#include "Weapon.h"
#include "../Constants.h"
#include "../Map.h"
#include "../../common_src/Timer.h"
#include <random>

Chain_gun::Chain_gun(Map *map, Config *config) {
  this->max_damage = config.get_max_damage(CHAIN_GUN);
  this->max_spread = config.get_max_spread(CHAIN_GUN);
  this->map = map;
}

void Chain_gun::attack() {
  if (!this->is_in_cooldown() && this->has_ammo()) {
    float angle = this->get_shot_angle();
    this->fire(angle);
    this->last_shot_timer.start();
    this->inventory.spend_ammo(this->ammo_cost);
  }
}
float Chain_gun::get_shot_angle() {
  float angle = this->inventory.get_player().get_direction();
  // cuando mas tiempo paso desde el ultimo disparo menos afecta el spred. hasta
  // el tiempo de reset. REVISAR PARA QUE AUMENTE CON EL NUMERO DE DISPAROS.
  float angle_variation =
      rand() %
      (this->max_spread *
       std::min(this->last_shot_timer.elapsed_time(), this->stability_reset) /
       this->stability_reset);
}
