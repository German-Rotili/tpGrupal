#include "Inventory.h"


Player& Inventory::get_player(){
    return this->player;
}

    
Inventory::Inventory(Player &player) : player(player){
    //this->ammo = Config.initialammo;
    
}




int Inventory::get_ammo() { return this->ammo; }

void Inventory::spend_ammo(int ammo_spent){
    this->ammo -= ammo_spent;
    
}