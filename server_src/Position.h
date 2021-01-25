#ifndef __SERVER_POSITION_H__
#define __SERVER_POSITION_H__
#include "Map.h"
#include "Config.h"

//es la posicion del jugador. se encarga de guardarla, almacenarla y modificarla. 
// asumimos hitboxes rectangulares. 
//para el movimiento, asumimos que en un comando de movimiento que depende de la velocidad, no puede recorrer el grosor de una pared.
// implementar con hitbox?
//verifica 

class Position{
private:
    float x;
    float y;
    float angle;
    float hitbox_radius;
    float linear_vel;
    float angular_vel;
    //Map &map;
    Map map;
    float get_new_x(char);
    float get_new_y(char);
    float get_y_offset(char);
    float get_x_offset(char);
    void update_angle(char);
public:
    Position(Map & map, Config &);
    ~Position();
    void update(char);
    float get_pos_x();
    float get_pos_y();
    float get_hitbox_radius();
    float get_angle();
    void get_attacked(int dmg);
    int colides(Position &);    
    float get_distance(float x, float y);
    float get_distance(Position &position);
};



#endif // __SERVER_POSITION_H__