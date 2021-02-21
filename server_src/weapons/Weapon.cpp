#include "Weapon.h"
#include "../Player.h"
#include "../../common_src/Timer.h"
#include "../HitscanRaycast.h"
#include "../Inventory.h"
#include "../Map.h"
#include <chrono>
#include <iostream>
void Weapon::fire(float angle) {
  /*
  tira un raycast. se obtiene la posicion maxima.
  se arma una recta con vector director sacado del angulo y posicion para el
  punto. se itera sobre los personajes vivos, por cada jugador armamos una recta
  para cada lado de su hitbox que de cara al jugador, si el que dispara esta
  para los x negativos e y positivos solo veo si colisiona co esas 2 caras del
  cuadrado hitbox. con las 2 rectas armo una matriz que me da los 2 parametros
  lmabda de las rectas donde colisionan. veo que los parametros esten en los
  rangos permitidos. de 0 al necesario para que colisione en el caso del que
  dispara y 2x radio de hitbox para el player una vez que tengo el o los
  jugadores que reciban el disparo mando al que tenga menor modulo de parametro
  que fue atacado

  verifico que el arma no sea un cuchillo, la logica es diferente.
  el arma solo me da el daño y conoce su cooldown. si le pido disparar y no me
  deja es porque todavia no puedo. en el caso de la ametralladora una vez que se
  apreta el boton dispara SOLA  la rafaga imeplementar con logica de paso de
  tiempo ya sea game loop o con algun evento.


  OPTIMIZACIONES:
         lo de la cara que apunta y tambien que el jugador este en la direccion
  del disparo. si el disparo tiene direccion x pos y el otro esta en x menor
  entonces ni verifico. si quiero meter 100000 jugadores se puede implementar
  una logica que separe el mapa en cuartos, una vez echo se puede verificar que
  jugadores estan en el mismo ambiente o cuarto y solo iterar sobre esos, ademas
  de todo lo anterior. teniendo el X max o min, y el Y max o min, puedo ignorar
  a los jugadores con coordenadas fuera de las permitidas

  CASOS BORDES:
    el jugador esta fuera del cuadrado permitido pero adentro de la hitbox.
  tendria que pegar.


  */
  HitscanRaycast raycaster;
  std::pair<float, float> impact =
      raycaster.get_impact_point(this->map, this->inventory->get_player());
  std::cout << "impact point x : " << impact.first << " impact point y : " << impact.second << std::endl;
  float xpos, ypos;
  xpos = this->inventory->get_player()->get_pos_x();
  ypos = this->inventory->get_player()->get_pos_y();
  int xdir, ydir;
  if (angle < 180) {
    ydir = 1;
  } else {
    ydir = -1;
  }
  if (angle < 90 || angle > 270) {
    xdir = 1;
  } else {
    xdir = -1;
  }

  float dist;
  Player *player_hit;
  float distance = 0;

  for (Player *player : this->map->get_players()) {
    float playerx = player->get_pos_x();
    float playery = player->get_pos_x();
    float hitboxRadius = player->get_hitbox_radius();

    if (((impact.first - player->get_pos_x()) * xdir) > 0) {
      if (((impact.second - player->get_pos_y()) * ydir) > 0) {
        if (((player->get_pos_x() - xpos) * xdir) > 0) {
          if (((player->get_pos_y() - ypos) * ydir) > 0) {
            /*
              logica de interseccion: por algebra, encuentro la interseccion de
              la recta jugador, impacto y busco la inter con la recta que
              contiene a cada lado de la hitbox del jugador, finalmente resto
              esta interseccion con el centro del lado es decir, la posicion del
              jugador, y veo que su modulo sea menor a la mitad de la longitud
              del lado de la hitbox.
              funciona de esta forma tan simple porque las lineas de los lados
              de la hitbox es paralela a los ejes.
            */
            float xhitbox = playerx - (hitboxRadius * xdir);
            float yhitbox = playery - (hitboxRadius * ydir);
            float lambda = (impact.second - xpos) * (yhitbox - playery);
            float xintersection =
                ((impact.second - xpos) * (yhitbox - playery) /
                 (impact.first - ypos)) +
                xpos;
            if (abs(xintersection - playerx) < hitboxRadius &&
                (distance == 0 || lambda < distance)) {
              player_hit = player;
              distance = lambda;
            }
            float yintersection = ((impact.first - ypos) * (xhitbox - playerx) /
                                   (impact.second - xpos)) +
                                  ypos;
            if (abs(yintersection - playery) < hitboxRadius &&
                (distance == 0 || lambda < distance)) {
              player_hit = player;
              distance = lambda;
            }
          }
        }
      }
    }
  }
  // una vez que termino las colisiones
  if (distance != 0) {
    player_hit->get_damaged(this->get_damage(distance));
    // appendear la accion al helper de acciones.
  }
  this->map->add_action(this->inventory->get_player()->get_id(), this->inventory->get_current_weapon_id(),impact.first,impact.second);
}

bool Weapon::is_in_cooldown() {
  if (!this->last_shot_timer.is_running()) {
    return false;
  }
  return (this->last_shot_timer.elapsed_time() < this->cooldown);
}

bool Weapon::has_ammo() {
  return this->inventory->get_ammo() >= this->ammo_cost;
}

float Weapon::get_shot_angle()
{
  return this->inventory->get_player()->get_direction();
}



Weapon::Weapon(Map *map, Config *config, Inventory *inventory) 
{
  this->map = map;
  this->inventory = inventory;
  this->config = config;
  this->last_shot_timer.start();
}


int Weapon::get_damage(int distance) {
  // disminuye el rango maximo en funcion de la distancia. por ahora,
  // linealmente. (lo que es horrible.) pero puede hacer daño maximo antes del
  // max range.
  int damage = rand() % (this->max_damage * this->max_acurate_range /
                         std::max(distance, this->max_acurate_range));
  return damage;
}