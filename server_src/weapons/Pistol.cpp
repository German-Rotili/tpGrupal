#include "../Config.h"
#include "Pistol.h"
#include "../Constants.h"
#include <random>
#include "../../common_src/Timer.h"
#include "Weapon.h"
#include "../Map.h"
#include <iostream>
/*
    imlementar con el tick la idea de no poder mantener apretado. 
*/



Pistol::Pistol(Map *map, Config *config, Inventory *inventory) : Weapon{map, config, inventory} {
    this->max_damage = 20; //config->get_max_damage(PISTOL);
    this->max_spread = 5; //config->get_max_spread(PISTOL);
    this->inventory = inventory;
}



void Pistol::attack(){
    if (!this->is_in_cooldown() && this->has_ammo()){
        float angle = this->get_shot_angle();
        this->fire(angle);
        this->last_shot_timer.start();
        this->inventory->spend_ammo(this->ammo_cost);
    }
}
float Pistol::get_shot_angle(){
    float angle = this->inventory->get_player()->get_direction();
    // cuando mas tiempo paso desde el ultimo disparo menos afecta el spred. hasta el tiempo de reset.
    float angle_variation = rand() % (this->max_spread * std::min(this->last_shot_timer.elapsed_time(), this->stability_reset) /this->stability_reset );
    std::cout << "random number is: " << angle_variation << std::endl;
    return angle + angle_variation;
}


