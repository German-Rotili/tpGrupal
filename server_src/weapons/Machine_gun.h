#include "Weapon.h"


class  Machine_gun : public Weapon{
private:
  float get_shot_angle() override;
  bool is_in_burst;
  int burst_counter;
  int burst_lenght; //config
  void start_burst();
  Timer burst_timer;

public:
     Machine_gun(Map &, Config &);
    ~ Machine_gun();
    void tick();
    void attack();
    bool can_fire_next_burst_shot();
};
