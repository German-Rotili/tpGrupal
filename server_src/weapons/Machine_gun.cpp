#include "Machine_gun.h"
#include "../Config.h"
#include "../Constants.h"
#include "Weapon.h"
#include "../Map.h"
#include "../../common_src/Timer.h"
#include <random>


Machine_gun::Machine_gun(Map &map, Config &config) {
  this->max_damage = config.get_max_damage(MACHINE_GUN);
  this->max_spread = config.get_max_spread(MACHINE_GUN);
  this->map = map;
}

void Machine_gun::tick() {
  if (this->is_in_burst) {
    float angle = this->get_shot_angle();
    this->fire(angle);
    this->last_shot_timer.start();
    this->inventory.spend_ammo(this->ammo_cost);
    this->burst_counter += 1;
    // check if voley is over.
    if(this->burst_counter >= this->burst_lenght || this->has_ammo()){
        this->is_in_burst = false;
    }
  }
}

void Machine_gun::attack() {
  if (!this->is_in_cooldown() && this->has_ammo() && !this->is_in_burst) {
    this->start_burst();
  }
}

float Machine_gun::get_shot_angle() {
  float angle = this->inventory.get_player().get_direction();
  // cuando mas tiempo paso desde el ultimo disparo menos afecta el spred. hasta
  // el tiempo de reset. REVISAR PARA QUE AUMENTE CON EL NUMERO DE DISPAROS.
  float angle_variation =
      std::rand() %
      (this->max_spread *
       std::min(this->last_shot_timer.elapsed_time(), this->stability_reset) /
       this->stability_reset);
}




