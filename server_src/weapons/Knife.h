#include "Weapon.h"


class  Knife : public Weapon{
private:
    /* data */
    float range;
    int damage;
public:
     Knife(Map &, Config &);
    ~ Knife();
    void attack();
};


/*
    itera sobre jugadores, si estan en el radio de ataque, verifica que por el angulo pueda atacarlo. 
    logica muy similar a las puertas. 

*/