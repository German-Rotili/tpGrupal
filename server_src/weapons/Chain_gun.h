#ifndef __CHAIN_GUN_H__
#define __CHAIN_GUN_H__

#include "Weapon.h"
class Map;
class Config;

class  Chain_gun : public Weapon{
private:
  float get_shot_angle() override;
  
public:
     Chain_gun(Map *, Config *, Inventory *);
    void attack();

};

#endif // __CHAIN_GUN_H__