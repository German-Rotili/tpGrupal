#include "Inventory.h"
#include "weapons/Knife.h"
#include "weapons/Pistol.h"
#include "weapons/Machine_gun.h"
#include "weapons/Chain_gun.h"
#include "weapons/Rocket_launcher.h"

#include <memory>

Player &Inventory::get_player() { return *this->player; }

void Inventory::attack() { this->weapons[current_weapon]->attack(); }

int Inventory::get_ammo() { return this->ammo; }

void Inventory::spend_ammo(int ammo_spent) { this->ammo -= ammo_spent; }

char Inventory::get_current_weapon_id() { return this->current_weapon; }

bool Inventory::handle_item(char id) 
{
  if(id == 49){
    this->add_ammo();
    return true;
  }
  if(id == 50){
    if(!this->owned_weapons[MACHINE_GUN]){
      this->owned_weapons[MACHINE_GUN] = true;
      return true;
    }
    return false;
  }
  if(id == 51){
    if(!this->owned_weapons[CHAIN_GUN]){
      this->owned_weapons[CHAIN_GUN] = true;
      return true;
    }
    return false;
  }
  if(id == 52){
    if(!this->owned_weapons[ROCKET_LAUNCHER]){
      this->owned_weapons[ROCKET_LAUNCHER] = true;
      return true;
    }
    return false;
  }
}



Inventory::Inventory(Player &player, Map &Map, Config &config) {
  this->player = &player;
  this->map = map;
  this->weapons[KNIFE] = std::make_unique<Knife>(this->map, this->config);
  this->weapons[PISTOL] = std::make_unique<Pistol>(this->map, this->config);
  this->weapons[MACHINE_GUN] = std::make_unique<Machine_gun>(this->map, this->config);
  this->weapons[CHAIN_GUN] = std::make_unique<Chain_gun>(this->map, this->config);
  this->weapons[ROCKET_LAUNCHER] = std::make_unique<Rocket_launcher>(this->map, this->config);

  this->owned_weapons[KNIFE] = true;
  this->owned_weapons[PISTOL] = true;
  

  // this->ammo = Config.initialammo;
}


