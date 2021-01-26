Como iniciar las partidas y unirse a partidas ya existentes.
Pasaje de mapas hechos por el editor.
Hablar esquema de partidas y como se comunican entre cliente y servidor

**To Do:**
    -Hacer que funcione el movimiento 100%
        .un quilombo de testear hasta que este el client, con la comunicacion se puede
    -ticker
        el tema de los eventos no funciona. implementar como una funcion que manda al server y luego este a todos los que la requieran. 
    -implementar disparo
    -implementar cambio de armas
    -implementar logica de puertas
    


vector bloqueante de intenciones. 

**Juego**

    Thread Server(main) -> Thread para cada cliente -> Thread para enviar y otro para recibir por cada cliente.

    En ThClient, creo al Player, le mando al Map una referencia del player.


**Comunicacion**

Cliente a Servidor [INTENCIONES] (STRUCT)

    Weapon 1-2-3-4

    Movement w-a-s-d

    Shoot space


Servidor a Cliente

    Informacion Inicial (STRUCT + YAML):

        Partidas

        Mapa


    Actualizaciones:

        Otros Jugadores: ID, Posicion Completa (x,y,ang), arma, disparando


    (    0x0000  
    (    SIZEMSG OTROS PLAYERS
    (
    (
    (    0x00  0x00 0x00 0x00 0x00 0x0 [tamanio fijo] -> [ Vector de char ]
    (    ID    X    Y    ANG  WEAP fire

        [La informacion de otros jugadores la tiene el Map, con lo cual hago un loop en el que voy mandando los datos de a un jugador por vez, armando un struct para cada uno]

        Objetos: Items Tirados, Puertas y ParedMovediza(tienen direccion), Cohetes.



        Tu Jugador: Posicion Completa, Todas las armas, Vida, Disparando.


    Informacion Final:

        Al finalizar la partida se deberá mostrar un top 5 de los jugadores con más enemigos matadas, más puntos por tesoros y más balas disparadas.
