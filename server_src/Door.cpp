#include "Door.h"

#include "../common_src/Timer.h"
#include <iostream>

Door::Door(char id) 
{
    this->last_open_timer.start();
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
    if(this->last_open_timer.elapsed_time() > this->door_cd){

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
    if(this->open && this->last_open_timer.elapsed_time() > open_time){
        this->toggle();
    }
}
