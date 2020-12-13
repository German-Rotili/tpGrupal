#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "server_Position.h"
#include "server_Map.h"
#include "server_Weapon.h"
#include "server_Inventory.h"


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
};
#endif