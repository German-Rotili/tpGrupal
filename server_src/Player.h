#ifndef __SERVER_PLAYER_H__
#define __SERVER_PLAYER_H__
#include <string>
#include "Position.h"
#include "Map.h"
#include "weapons/Weapon.h"
#include "Inventory.h"

//Para el manejo de las acciones. agregar una lista de acciones que ocurren en cada iteracion. para esto cuando el server 
//prepare el mensaje al cliente leera desde esta lista las acciones que son relevantes al cliente por ejemplo;
// dispara, abre puerta, recibe daño, etc. 

class Player{
private:
    Position position;
    bool is_alive;
    Map &map;
    Inventory inventory;
    Weapon *current_weapon;
    void move(char intention);
    void attack();
    void acction();
    void intersects(float impx, float impy, Player &player);

public:
    Player(Map,Position position);
    Player(Map,float, float, float);
    ~Player();
    float get_pos_x();
    float get_pos_y();
    float get_direction();
    void execute_intention(char intention);
    void get_damaged(int damage);
    void game_tick();
    float get_hitbox_radius();
};

#endif // __SERVER_PLAYER_H__