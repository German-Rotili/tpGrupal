#include "Player.h"
#include "Inventory.h"
#include "weapons/Knife.h"
#include "weapons/Pistol.h"
#include "weapons/Machine_gun.h"
#include "weapons/Chain_gun.h"
#include "weapons/Rocket_launcher.h"
#include "Constants.h"
#include "weapons/Weapon.h"
#include <memory>
#include <map>
#include "Map.h"
#include "Config.h"
#include <iostream>
#include <memory>

Player* Inventory::get_player() { return this->player; }

void Inventory::attack() { 
  // std::cout << this->get_player()->get_direction() << "DIRECCION";
this->weapons[current_weapon]->attack(); 
  }

int Inventory::get_ammo() { return this->ammo; }

void Inventory::spend_ammo(int ammo_spent) { this->ammo -= ammo_spent; }

void Inventory::add_ammo() 
{
  this->ammo += 20;
}

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
  return false;
}

void Inventory::tick() 
{
  this->weapons[MACHINE_GUN]->tick();
}


Inventory::Inventory(Player *player_passed, Map *map, Config *config) {
  this->map = map;
  this->config = config;
  this->player = player_passed;
  this->weapons[KNIFE] = new Knife(this->map, this->config, this);
  this->weapons[PISTOL] = new Pistol(this->map, this->config, this);
  this->weapons[MACHINE_GUN] = new Machine_gun(this->map, this->config, this);
  this->weapons[CHAIN_GUN] = new Chain_gun(this->map, this->config, this);
  this->weapons[ROCKET_LAUNCHER] = new Rocket_launcher(this->map, this->config, this);

  this->owned_weapons[KNIFE] = true;
  this->owned_weapons[PISTOL] = true;
  this->owned_weapons[MACHINE_GUN] = true;
  this->current_weapon = 1;
  this->ammo = 300;
  

  // this->ammo = Config.initialammo;
}

bool Inventory::change_weapon(int intention) 
{
  if(this->owned_weapons[intention]){
    this->current_weapon = intention;
  }
}


