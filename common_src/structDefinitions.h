#ifndef __STRUCTDEFINITIONS_H__
#define __STRUCTDEFINITIONS_H__

enum WeaponType {GUN, MACHINE_GUN, MINIGUN, ROCKET_LAUNCHER};

typedef struct
{
  WeaponType type;
  int speed;
  int ammo;
  int damage;
} weaponStats_t;

typedef struct
{
  int speed;
  int health;
} actorStats_t;

#endif // __STRUCTDEFINITIONS_H__
