#ifndef __MACHINE_GUN_H__
#define __MACHINE_GUN_H__
#include "Weapon.h"
class Map;
class Config;

class  Machine_gun : public Weapon{
private:
  float get_shot_angle() override;
  bool is_in_burst = false;
  int burst_counter = 0;
  int burst_lenght = 5; //config
  int burst_cooldown = 200;
  void start_burst();
  Timer burst_timer;
  bool is_burst_in_cooldown();

public:
    Machine_gun(Map *, ServerConfigHandler *,Inventory *);
    void tick();
    void attack();
    bool can_fire_next_burst_shot();
};

#endif // __MACHINE_GUN_H__