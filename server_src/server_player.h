#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "server_Position.h"
#include "server_Map.h"


class Player{
private:
    Position position;
    void move(char intention);
    void attack();
    Map &map;
public:
    Player(Position position);
    ~Player();
    int get_pos_x();
    int get_pos_y();
    void execute_intention(char intention);
};
#endif