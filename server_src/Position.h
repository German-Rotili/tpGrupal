#ifndef __SERVER_POSITION_H__
#define __SERVER_POSITION_H__


//es la posicion del jugador. se encarga de guardarla, almacenarla y modificarla. 
// asumimos hitboxes rectangulares. 
//para el movimiento, asumimos que en un comando de movimiento que depende de la velocidad, no puede recorrer el grosor de una pared.
// implementar con hitbox?
//verifica 
class Map;
class Config;

class Position{
private:
    float x;
    float y;
    float angle = 10;
    float hitbox_radius = 0.4;
    float linear_vel = 0.03;
    float angular_vel = 10;
    Map *map;
    Config *config;
    float get_new_x(char);
    float get_new_y(char);
    float get_y_offset(char);
    float get_x_offset(char);
    void update_angle(char);
public:

    Position(Map *, Config *);
    void update(char);
    float get_pos_x();
    float get_pos_y();
    float get_hitbox_radius();
    float get_angle();
    void set_position(int x, int y);
   
   
    void get_attacked(int dmg);
    int colides(Position &);    
    float get_distance(float x, float y);
    float get_distance(Position &position);
    bool is_in_hitbox(float x, float y);
    float get_angle_difference(Position position);
    float get_angle_difference(float x, float y);


};



#endif // __SERVER_POSITION_H__