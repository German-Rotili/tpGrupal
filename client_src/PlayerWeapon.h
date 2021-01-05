#ifndef PLAYERWEAPON_H
#define PLAYERWEAPON_H

#define BALAS_INF 999

class PlayerWeapon {
  bool disponible;
  int cantBalas;

  public:
   PlayerWeapon(bool obtenida, int balasIniciales);
   ~PlayerWeapon();
   void setCantBalas(int balasActuales);
   int getCantBalas() const;
   bool estaDisponible() const;
};

#endif
