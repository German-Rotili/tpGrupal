#include "Door.h"

#include "../common_src/Timer.h"
#include <iostream>

Door::Door(char id) 
{
    this->last_open_timer.start();
    this->id = id;
    if(this->id >= 59 && this->id <= 62) this->locked = true;

}

char Door::get_id() 
{
    return this->id;
}

bool Door::is_open() 
{
    return this->open;
}

bool Door::is_walkable() 
{
    return this->walkable;
}

void Door::toggle() 
{
    if(this->last_open_timer.elapsed_time() > this->door_cd && !this->locked){

        if(this->is_open()){
            this->open = false;
        } else { 

            this->open = true; 
            }

        this->last_open_timer.start();
        this->walkable = this->open;
    }
}

void Door::tick() 
{   
    if(this->open && (this->last_open_timer.elapsed_time() > open_time)){
        this->toggle();
    }
}



bool Door::unlock(char key_id) 
{   if(((this->id == 59 || this->id == 60) && key_id == 44) || (this->id == 61 || this->id == 62) && key_id == 45) {
        this->locked = false;
        return true;
    }
    return false;

}

bool Door::is_locked() 
{
    return this->locked;
}
