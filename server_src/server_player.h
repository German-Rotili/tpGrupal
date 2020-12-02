#ifndef PLAYER_H
#define PLAYER_H
#include <string>

class Player{
private:
    int & pos_x;
    int & pos_y;
    std::string & orientation;

public:
    void update_position(int & pos_x, int & pos_y, std::string dir);
    Player(int & pos_x, int &  pos_y, std::string & orientation);
    int get_pos_x();
    int get_pos_y();
    ~Player();
};
#endif