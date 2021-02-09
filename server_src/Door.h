#ifndef __DOOR_H__
#define __DOOR_H__

#include "../common_src/Timer.h"

class Timer;

class Door
{
private:

    Timer last_open_timer;
    int door_cd;
    bool open = false;
    bool walkable = false;

public:
    Door(char id);
    ~Door();
    bool is_open();
    bool is_walkable();
    void toggle();
};




Door::~Door()
{
}

#endif // __DOOR_H__