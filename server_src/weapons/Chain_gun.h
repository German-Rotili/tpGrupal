#include "Weapon.h"


class  Chain_gun : public Weapon{
private:
  float get_shot_angle() override;
public:
     Chain_gun(Map &, Config &);
    ~ Chain_gun();
    void attack();

};
