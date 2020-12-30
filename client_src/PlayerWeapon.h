#ifndef PLAYERWEAPON_H
#define PLAYERWEAPON_H

#define BALAS_INF 999

class PlayerWeapon {
  bool obtenida;
  int cantBalas;

  public:
   PlayerWeapon(bool obtenida, int balasIniciales);
   ~PlayerWeapon();
   int getCantBalas();
   void setCantBalas(int balasActuales);
   bool estaEnInventario();
};

#endif
