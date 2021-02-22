#ifndef __SERVER_INVENTORY_H__
#define __SERVER_INVENTORY_H__
#include "Constants.h"
#include <memory>
#include <map>
class Weapon;
class Config;
class Player;
class Map;

class Inventory{

    // aca hardcodeamos todas las armas. despues tiene una lista de armas que si tiene y una que es la actual. me parece mas simple y
    //evitamos pedir memoria. todo el juego puede correr en stack por ahora en el server.

private:
    Player *player;
    int ammo = 300;
    char current_weapon = 1;
    std::map<char, Weapon*> weapons;
    bool owned_weapons[NUMBER_OF_WEAPONS];
    Map *map;
    Config *config;

public:
    Inventory(Player*, Map*, Config *);
    bool pick_up_weapon();
    void change_weapon(char);
    Player* get_player();
    void attack();
    int get_ammo();
    void spend_ammo(int);
    void add_ammo();
    char get_current_weapon_id();
    bool* get_weapons();
    bool handle_item(char id);
    void tick();

    
};


#endif // __SERVER_INVENTORY_H__