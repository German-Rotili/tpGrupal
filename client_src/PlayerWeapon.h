#ifndef PLAYERWEAPON_H
#define PLAYERWEAPON_H

#include <string>
#include "SDLWrappers/SdlSound.h"

class PlayerWeapon {
  bool disponible;
  SdlSound& sonido1;
  SdlSound& sonido2;

  public:
   PlayerWeapon(bool obtenida, SdlSound& sonido1, SdlSound& sonido2);
   ~PlayerWeapon();
   bool estaDisponible() const;
   void reproducirSonido() const;
};

#endif
