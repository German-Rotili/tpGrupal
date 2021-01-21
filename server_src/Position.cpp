#include "Position.h"
#include <math.h> 
#define FORWARD 'w'
#define BACKWARDS 'S'
#define RIGHT 'd'
#define LEFT 'a'
#define PI 3.14159265

void Position::update(char mov) {
    if(mov == FORWARD || mov == BACKWARDS){
        float offset_x = this->get_y_offset(mov);
        float offset_y = this->get_x_offset(mov);
        int new_x = (int)(this->x + offset_x);
        int new_y = (int)this->y;

        int hitbox_limit_x = (offset_x > 0) ? new_x + this->hitbox_radius : new_x - this->hitbox_radius;

        if(this->map.valid_position(hitbox_limit_x, new_y)){
            this->x = new_x;    
        }else{ //si se choca contra una pared muevo el personaje para que la hitbox este justo al limite.
            this->x = (this->x < new_x) ? new_x - this->hitbox_radius : new_x + hitbox_radius;
        }
        new_x = (int)(this->x);
        new_y = (int)this->y + offset_y;

        int hitbox_limit_y = (offset_y > 0) ? new_y + this->hitbox_radius : new_y - this->hitbox_radius;
        if(this->map.valid_position(new_x, hitbox_limit_y)){
            this->x = new_x;    
        }else{ //si se choca contra una pared muevo el personaje para que la hitbox este justo al limite.
            this->y = (this->y < new_y) ? new_y - this->hitbox_radius : new_y + hitbox_radius;
        }
    } else{
        this->update_angle(mov);
    }

}

float Position::get_pos_x() { return this->x; }

float Position::get_pos_y() { return this->y; }

float Position::get_hitbox_radius() {return this->hitbox_radius;}

float Position::get_angle() { return this->angle; }

int Position::colides(Position &) { return 1;}

float Position::get_y_offset(char intention){
    if(intention == FORWARD){
        return this->linear_vel * sin(this->angle * PI/180);
    }
    else if(intention == BACKWARDS){
        return - this->linear_vel * sin(this->angle * PI/180);
    }
    else {return 0;}
}

float Position::get_x_offset(char intention){
    if(intention == FORWARD){
        return this->linear_vel * cos(this->angle * PI/180);
    }
    else if(intention == BACKWARDS){
        return - this->linear_vel * cos(this->angle * PI/180);
    }
    else {
        return 0;
    }
}

void Position::update_angle(char intention){
    if(intention == RIGHT){
        this->angle -=this->angular_vel;
    }
    if(intention == LEFT){
        this->angle -=this->angular_vel;
    }

    //no es necesario esto realmente. pero me gustaria que se mantenga el angulo entre 0 y 360. 
    //quizas en una hora de juego hacemos un overflow sino. 
    this->angle = (this->angle < 0) ? 360 + this->angle : this->angle;
    this->angle = (this->angle > 360) ? this->angle - 360 : this-> angle;
    
}
    

