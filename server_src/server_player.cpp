#include "server_player.h"
#include <iostream>
#include "Constants.h"


void Player::execute_intention(char intention){
    if(this->is_alive){
        if(intention == FORWARD || intention == BACKWARDS || intention == RIGHT || intention == LEFT){
            this->position.update(intention);
        }
        if(intention == ACTION){
            this->acction();
        }
        if(intention == ATTACK){
            this->attack();
        }
    }
}






void Player::attack(){
    /*
    tira un raycast. se obtiene la posicion maxima. 
    se arma una recta con vector director sacado del angulo y posicion para el punto. 
    se itera sobre los personajes vivos, por cada jugador armamos una recta para cada lado de su hitbox que de cara al jugador, 
    si el que dispara esta para los x negativos e y positivos solo veo si colisiona co esas 2 caras del cuadrado hitbox. 
    con las 2 rectas armo una matriz que me da los 2 parametros lmabda de las rectas donde colisionan. veo que los parametros esten 
    en los rangos permitidos. de 0 al necesario para que colisione en el caso del que dispara y 2x radio de hitbox para el player
    una vez que tengo el o los jugadores que reciban el disparo mando al que tenga menor modulo de parametro que fue atacado

    verifico que el arma no sea un cuchillo, la logica es diferente. 
    el arma solo me da el daño y conoce su cooldown. si le pido disparar y no me deja es porque todavia no puedo. 
    en el caso de la ametralladora una vez que se apreta el boton dispara SOLA  la rafaga imeplementar con logica de paso de tiempo
    ya sea game loop o con algun evento. 


    OPTIMIZACIONES:
           lo de la cara que apunta y tambien que el jugador este en la direccion del disparo. si el disparo tiene direccion x pos y el 
           otro esta en x menor entonces ni verifico. 
           si quiero meter 100000 jugadores se puede implementar una logica que separe el mapa en cuartos, una vez echo se puede 
           verificar que jugadores estan en el mismo ambiente o cuarto y solo iterar sobre esos, ademas de todo lo anterior. 
           teniendo el X max o min, y el Y max o min, puedo ignorar a los jugadores con coordenadas fuera de las permitidas
    */
}

void Player::acction(){
    //si esta cerca de una puerta la abre. super idiota. 
    
}
