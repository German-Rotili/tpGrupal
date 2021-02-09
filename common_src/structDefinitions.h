#ifndef __STRUCTDEFINITIONS_H__
#define __STRUCTDEFINITIONS_H__

enum WeaponType {KNFIE, GUN, MACHINEGUN, MINIGUN, ROCKETLAUNCHER};

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

struct object_t{
    int id;
    double pos_x;
    double pos_y;
    bool state;
};


struct intention_t{
  char up;
  char angle_right;
  char angle_left;
  char down;
  char attack;
  char interact;
  char weapon;
};

struct player_t {
    int player_id;
    float pos_x;
    float pos_y;
    float direction;
    int ammo;
    char current_weapon;
    double health;
    int lives;
    int score;
};

#endif // __STRUCTDEFINITIONS_H__
