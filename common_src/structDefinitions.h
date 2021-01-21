#ifndef STRUCTDEFINITIONS
#define STRUCTDEFINITIONS
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
  int max_ammo;
} actorStats_t;
#endif
