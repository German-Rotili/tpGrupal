#ifndef __MACHINE_GUN_H__
#define __MACHINE_GUN_H__
#include "Weapon.h"
class Map;
class Config;

class  Machine_gun : public Weapon{
private:
  float get_shot_angle() override;
  bool is_in_burst;
  int burst_counter;
  int burst_lenght; //config
  void start_burst();
  Timer burst_timer;

public:
     Machine_gun(Map *, Config *);
    void tick();
    void attack();
    bool can_fire_next_burst_shot();
};

#endif // __MACHINE_GUN_H__