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
#include "ServerConfigHandler.h"
#include <iostream>
#include <memory>
#include <iostream>
Player* Inventory::get_player() { return this->player; }

void Inventory::attack() { 
  // std::cout << this->get_player()->get_direction() << "DIRECCION";
this->weapons[current_weapon]->attack(); 
  }

int Inventory::get_ammo() { return this->ammo; }

void Inventory::spend_ammo(int ammo_spent) { this->ammo -= ammo_spent; }

bool Inventory::add_ammo() 
{
  if(this->ammo == this->max_ammo) return false;
  this->ammo += 20;
  if(this->ammo > this->max_ammo) this->ammo = this->max_ammo;
  return true;
}

char Inventory::get_current_weapon_id() { return this->current_weapon; }

bool Inventory::handle_item(char id) 
{
  if(id == 49){
    return this->add_ammo();
  }
  if(id == 44 || id == 45){
    this->keys[id] += 1;
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
  if(this->ammo == 0){
    this->current_weapon = 0;
  }
  this->weapons[MACHINE_GUN]->tick();

}

std::map<char, int>& Inventory::get_keys() 
{
  return this->keys;
}

void Inventory::shot_fired() 
{
  this->shots_fired += 1;
}

int Inventory::get_shots_fired() 
{
  return this->shots_fired;
}

void Inventory::reset() 
{
  this->owned_weapons[KNIFE] = true;
  this->owned_weapons[PISTOL] = true;
  this->owned_weapons[MACHINE_GUN] = false;
  this->owned_weapons[CHAIN_GUN] = false;
  this->owned_weapons[ROCKET_LAUNCHER] = false;
  this->current_weapon = 1;
  this->ammo = 8;
  this->keys[44] = 0;
  this->keys[45] = 0;
  
}


Inventory::Inventory(Player *player_passed, Map *map, ServerConfigHandler *config) {
  this->map = map;
  this->config = config;
  this->player = player_passed;
  this->weapons[KNIFE] = new Knife(this->map, this->config, this);
  this->weapons[PISTOL] = new Pistol(this->map, this->config, this);
  this->weapons[MACHINE_GUN] = new Machine_gun(this->map, this->config, this);
  this->weapons[CHAIN_GUN] = new Chain_gun(this->map, this->config, this);
  this->weapons[ROCKET_LAUNCHER] = new Rocket_launcher(this->map, this->config, this);


  this->reset();

  // this->ammo = Config.initialammo;
}

Inventory::~Inventory() 
{
  delete this->weapons[KNIFE];
  delete this->weapons[PISTOL];
  delete this->weapons[MACHINE_GUN];
  delete this->weapons[CHAIN_GUN];
  delete this->weapons[ROCKET_LAUNCHER];
}

void Inventory::change_weapon(char intention) 
{
  if(this->ammo == 0) return;
  if(this->owned_weapons[intention]){
    this->current_weapon = intention;
  }
}


