#ifndef __DOOR_H__
#define __DOOR_H__

#include "../common_src/Timer.h"


class Door
{
private:

    Timer last_open_timer;
    int door_cd = 200;
    bool open = false;
    bool walkable = false;
    int open_time = 10000;
    char id;
    bool locked = false;
public:

    Door(char id);
    char get_id();
    bool is_open();
    bool is_walkable();
    void toggle();
    void tick();
    bool unlock(char );
    bool is_locked();
};





#endif // __DOOR_H__