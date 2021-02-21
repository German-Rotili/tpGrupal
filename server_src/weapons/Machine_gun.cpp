#include "Machine_gun.h"
#include "../Config.h"
#include "../Constants.h"
#include "Weapon.h"
#include "../Map.h"
#include "../../common_src/Timer.h"
#include <random>
#include <iostream>

Machine_gun::Machine_gun(Map *map, Config *config, Inventory *inventory)  : Weapon{map, config, inventory} {
  this->max_damage = 20; //config->get_max_damage(MACHINE_GUN);
  this->max_spread = 5; //config->get_max_spread(MACHINE_GUN);
  this->map = map;
  this->cooldown = 50;
  this->burst_timer.start();

}

void Machine_gun::tick() {

  if (this->is_in_burst && !this->is_in_cooldown()) {
    std::cout << "tick" << std::endl;
    float angle = this->get_shot_angle();
    this->fire(angle);
    this->last_shot_timer.start();
    this->inventory->spend_ammo(this->ammo_cost);
    this->burst_counter += 1;
    // check if voley is over.
    if(this->burst_counter >= this->burst_lenght && this->has_ammo()){
        this->is_in_burst = false;
        this->burst_counter = 0;
        this->burst_timer.start();
    }
  }
}



void Machine_gun::attack() {
      std::cout << "MACHINE GUN ATTACK" << std::endl;

  if (!this->is_burst_in_cooldown() && this->has_ammo() && !this->is_in_burst) {
    this->start_burst();
  }
}

float Machine_gun::get_shot_angle() {
  float angle = this->inventory->get_player()->get_direction();
  // cuando mas tiempo paso desde el ultimo disparo menos afecta el spred. hasta
  // el tiempo de reset. REVISAR PARA QUE AUMENTE CON EL NUMERO DE DISPAROS.
  float angle_variation = 0;
    /*   std::rand() %
      (this->max_spread *
       std::min(this->last_shot_timer.elapsed_time(), this->stability_reset) /
       this->stability_reset); */
  return angle + angle_variation;
}

void Machine_gun::start_burst() 
{
  this->is_in_burst = true;
  this->tick();
}

bool Machine_gun::is_burst_in_cooldown() {
  if (!this->burst_timer.is_running()) {
    return false;
  }
  return (this->burst_timer.elapsed_time() < this->burst_cooldown);
}


