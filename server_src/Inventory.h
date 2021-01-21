#ifndef __SERVER_INVENTORY_H__
#define __SERVER_INVENTORY_H__
#include "Player.h"
class Inventory{

    // aca hardcodeamos todas las armas. despues tiene una lista de armas que si tiene y una que es la actual. me parece mas simple y
    //evitamos pedir memoria. todo el juego puede correr en stack por ahora en el server.

private:
    Player &player;
    int ammo;

public:
    Inventory(Player&);
    ~Inventory();
    bool pick_up_weapon();
    bool fire_current_weapon();
    bool change_weapon(char);
    Player& get_player();
    void attack();
    int get_ammo();
    void spend_ammo(int);

    
};


#endif // __SERVER_INVENTORY_H__