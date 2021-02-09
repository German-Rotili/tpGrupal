#ifndef __ROCKET_H__
#define __ROCKET_H__

class Map;
class Config;


class Rocket
{
private:
    float velocity;
    float explotion_radius;
    float damage;
    float direction;
    float x_pos;
    float y_pos;
    Map & map;
    Config &config;

    void explode();
    void update_position();
    float get_y_offset();
    float get_x_offset();
    bool colides_with_player(); //REVISAR si la velocidad es suficiente para pasar por la hitbox sin explotar. 

public:
    Rocket(Map & map, Config &config, float dir_x, float dir_y, float direction);
    ~Rocket();
    bool tick();
    float get_pos_x();
    float get_pos_y();

};


#endif // __ROCKET_H__