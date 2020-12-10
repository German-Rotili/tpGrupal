#include "server_Position.h"

void Position::update(char mov) {
    coordinate newpos;
    float offset_x = this->get_y_offset(mov);
    float offset_y = this->get_x_offset(mov);
    int new_x = (int)(this->x + offset_x);
    int new_y = (int)this->y;

    if(this->map.valid_position(new_x, new_y)){
        //implementar que no choque con otros players y si no choca updatea.
    }else{}
   //same para la x. 
   
    

}





float Position::get_pos_x() { return this->x; }

float Position::get_pos_y() { return this->y; }

float Position::get_angle() { return this->angle; }

int Position::colides(Position &) {}
