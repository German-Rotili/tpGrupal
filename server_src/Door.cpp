#include "Door.h"

#include "../common_src/Timer.h"


Door::Door(char id) 
{
    this->last_open_timer.start();
}

void Door::toggle() 
{
    if(this->last_open_timer.elapsed_time() < this->door_cd){
        if(this->is_open()){
            this->open = false;
        } else { this->open = true; }

        this->last_open_timer.start();
        this->walkable = this->open;
    }
}
