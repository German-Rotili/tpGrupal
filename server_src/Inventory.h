#ifndef __SERVER_INVENTORY_H__
#define __SERVER_INVENTORY_H__
#include "Player.h"
#include "Constants.h"
#include "../weapons/Weapon.h"
#include <memory>
#include <map>
#include "Map.h"
#include "Config.h"
class Inventory{

    // aca hardcodeamos todas las armas. despues tiene una lista de armas que si tiene y una que es la actual. me parece mas simple y
    //evitamos pedir memoria. todo el juego puede correr en stack por ahora en el server.

private:
    Player *player;
    int ammo;
    char current_weapon;
    std::map<char, std::unique_ptr<Weapon>> weapons;
    Map *map;
    Config config;
public:
    Inventory(Player&, Map&);
    ~Inventory();
    bool pick_up_weapon();
    bool change_weapon(char);
    Player& get_player();
    void attack();
    int get_ammo();
    void spend_ammo(int);
    char get_current_weapon_id();
    bool* get_weapons();
    
};


#endif // __SERVER_INVENTORY_H__