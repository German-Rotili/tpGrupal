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
    std::cout << "adentro del toggle" << std::endl;
    if(this->last_open_timer.elapsed_time() > this->door_cd){
    std::cout << "adentro del if" << std::endl;

        if(this->is_open()){
            this->open = false;
        } else { this->open = true; }

        this->last_open_timer.start();
        this->walkable = this->open;
    }
}
