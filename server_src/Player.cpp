#include "Player.h"
#include "Constants.h"
#include <iostream>
#include <tuple>
#include <utility>

void Player::execute_intention(char intention) {
  if (this->is_alive) {
    if (intention == FORWARD || intention == BACKWARDS || intention == RIGHT ||
        intention == LEFT) {
      this->position.update(intention);
    }
    if (intention == ACTION) {
      this->acction();
    }
    if (intention == ATTACK) {
      this->attack();
    }
  }
}

void Player::attack(){
  this->inventory.attack();
}

void Player::acction() {
  /* for(Door &door : this->map.get_doors()){
    if in range de distancia y angulo ya programado para cada x e y de puerta.
  } */

}

float Player::get_pos_x() { return this->position.get_pos_x(); }
float Player::get_pos_y() { return this->position.get_pos_y(); }
float Player::get_hitbox_radius() { return this->position.get_hitbox_radius(); }

float Player::get_distance(Position position) {
  return this->position.get_distance(position);
}

float Player::get_distance(float x, float y) {
  return this->position.get_distance(x, y);
}

float Player::get_angle_difference(Position position){
  return this->position.get_angle_difference(position);
}

float Player::get_angle_difference(float x, float y) {
    return this->position.get_angle_difference(x,y);

}

bool Player::is_in_hitbox(float x, float y) {
  return this->position.is_in_hitbox(x,y);  
}

int Player::get_ammo() 
{
  this->inventory.get_ammo();
}

char Player::get_current_weapon_id(){
  this->inventory.get_current_weapon_id();
}

float Player::get_direction() { return this->position.get_angle(); }


player_t Player::get_info(){
  player_t player_info;
  player_info.player_id = this->get_id();
  player_info.pos_x = this->get_pos_x();
  player_info.pos_y = this->get_pos_y();
  player_info.direction = this->get_direction();
  player_info.ammo = this->get_ammo();
  player_info.current_weapon = this->get_current_weapon_id();
  return player_info;
}



/* void Player::attack() {
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


  
  if(this->current_weapon->can_fire()){
    float angle = this->position.get_angle();
    float xpos, ypos;
    xpos = this->position.get_pos_x();
    ypos = this->position.get_pos_y();
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
    std::pair<float, float> impact= this->map.get_impact_point(*this);
    Player* player_hit;
    float distance;
    for (Player &player : this->map.get_players()) {
      float playerx = player.get_pos_x();
      float playery = player.get_pos_x();
      float hitboxRadius = player.get_hitbox_radius();

      if (((impact.first - player.get_pos_x()) * xdir) > 0) {
        if (((impact.second - player.get_pos_y()) * ydir) > 0) {
          if (((player.get_pos_x() - xpos) * xdir)) {
            if (((player.get_pos_y() - ypos) * ydir)) {
              /*
                logica de interseccion: por algebra, encuentro la interseccion de
                la recta jugador, impacto y busco la inter con la recta que
                contiene a cada lado de la hitbox del jugador, finalmente resto
                esta interseccion con el centro del lado es decir, la posicion del
                jugador, y veo que su modulo sea menor a la mitad de la longitud
                del lado de la hitbox.
                funciona de esta forma tan simple porque las lineas de los lados de la hitbox es paralela a los ejes. 
              
              float xhitbox = playerx - (hitboxRadius * xdir);
              float yhitbox = playery - (hitboxRadius * ydir);
              float lambda = (impact.second - xpos) * (yhitbox - playery);
              float xintersection = ((impact.second - xpos) * (yhitbox - playery)/(impact.first - ypos)) + xpos;
              if (abs(xintersection-playerx) < hitboxRadius && (distance == 0 || lambda < distance)){
                player_hit = &player;
                distance = lambda;
              }
              float yintersection = ((impact.first - ypos) * (xhitbox - playerx)/(impact.second - xpos)) + ypos;
              if (abs(yintersection-playery) < hitboxRadius && (distance == 0 || lambda < distance)){
                player_hit = &player;
                distance = lambda;
              }
            }
          }
        }
      }
    }
    //una vez que termino las colisiones
    if(distance != 0){
      player_hit->get_damaged(this->current_weapon->get_damage(distance));
      //appendear la accion al helper de acciones.
    }
  }

}
 */