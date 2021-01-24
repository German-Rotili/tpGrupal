#ifndef PLAYERWEAPON_H
#define PLAYERWEAPON_H

class PlayerWeapon {
  bool disponible;

  public:
   PlayerWeapon(bool obtenida);
   ~PlayerWeapon();
   bool estaDisponible() const;
};

#endif
