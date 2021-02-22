#ifndef __ROCKET_H__
#define __ROCKET_H__

#include "../Player.h"
#include "../Map.h"
#include "../ServerConfigHandler.h"
class Map;
class Player;
class Rocket
{
private:
    Player *player;
    float velocity = 0.1;
    float explotion_radius = 2;
    float damage = 10;
    float direction;
    float x_pos;
    float y_pos;
    Map * map;
    ServerConfigHandler *config;

    void explode();
    void update_position();
    float get_y_offset();
    float get_x_offset();
    bool colides_with_player(); //REVISAR si la velocidad es suficiente para pasar por la hitbox sin explotar. 

public:
    Rocket(Map *, ServerConfigHandler *,Player *, float dir_x, float dir_y, float direction);

    bool tick();
    float get_pos_x();
    float get_pos_y();

};


#endif // __ROCKET_H__