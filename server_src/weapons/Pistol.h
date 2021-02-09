#ifndef __PISTOL_H__
#define __PISTOL_H__

#include "Weapon.h"
class Map;
class Config;

class Pistol : public Weapon {
private:
  float get_shot_angle() override;
  

public:
  Pistol(Map *, Config *);
  ~Pistol();
  void attack();
};

#endif // __PISTOL_H__