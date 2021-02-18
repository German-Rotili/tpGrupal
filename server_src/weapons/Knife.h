#ifndef __KNIFE_H__
#define __KNIFE_H__

#include "Weapon.h"
class Map;
class Config;

class  Knife : public Weapon{
private:
    /* data */
    float range;
    int damage;
public:
     Knife(Map *, Config *, Inventory *);
    void attack();
};


/*
    itera sobre jugadores, si estan en el radio de ataque, verifica que por el angulo pueda atacarlo. 
    logica muy similar a las puertas. 

*/
#endif // __KNIFE_H__