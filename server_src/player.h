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
    Inventory weapons;
    Weapon *current_weapon;
    void move(char intention);
    void attack();
    void acction();

public:
    Player(Position position);
    ~Player();
    int get_pos_x();
    int get_pos_y();
    void execute_intention(char intention);
    void get_damaged(int damage);
    
};

#endif // __SERVER_PLAYER_H__