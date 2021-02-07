#include "ThClient.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include "../editor_src/ConfigManager/MapHandler.h"
#include <string>
#include <fstream>
#include <streambuf>
//#include "Player.h"
#include <iterator>
#include "ThClientSender.h"
#include "../common_src/Action.h"
#include "../common_src/Serializer.h"

#include <chrono>
#define FPS 30

void ThClient::run(){
    try {
        //acepto un nuevo cliente, tiene que elegir la partida o crear nueva
        //Le mando los id de las partidas que tengo y el id de los mapas para que cree una nueva partida?
        //recibo cantidad de players que va a tener la partida?

        //new game(recibe el mapa del cliente)- join game - refresh

        //new game

                //std::vector<char> cmd(CHUNK_SZ,0);
                //std::string output = game_handler.show_matches();
                //peer.socket_send(output.c_str(), output.length());
                //peer.socket_recieve(output.c_str(), output.length());
                //Parseo la partida que eligio y la asigno al cliente.

        //std::string id;
        //GamePlay game_play = game_handler.select_match(id);
        //or
        //GamePlay game_play = game_handler.new_match();

        
                    //la idea es que el mapa lea las intenciones pero se bloquea.
                    //el mapa le pide las intenciones a cada jugador, vector de chars, quizas limitado.
                    //la idea seria que el game loop este en el gameplay
                    //El cliente solo recibe intenciones y manda snapshots.
                    //El cliente recibe del gameplay cuando termina.
                    //





        ThClientSender ThSender(this->peer, *(this->action), this->snapshot);
        ThSender.start();


     

        /*ENVIO SNAPSHOT DEL JUGADOR*/

        //incluir estado de puerta, el cliente se encarga de ver si cambio con una copia del estado anterior.




          /*******ACCIONES**********/
        /*************************/



        // cola de eventos en el cliente cuando parsea una accion.

        // char action_id = '1';
        // char snapshot_id = '0';

        // Serializer serializer;
        // std::vector <char> msg = serializer.serialize(player);
        // peer.socket_send(&snapshot_id, sizeof(char));
        // uint32_t snap_size = htonl(msg.size());
        // peer.socket_send((char*)&snap_size, sizeof(uint32_t));
        // peer.socket_send(msg.data(), msg.size());
        /*********************************/

        intention_t intention;
        intention.active = false;
        Serializer serializer;

        /*GAME LOOP tiene que ir a GAMEPLAY!*/
        while (state){
            std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

            uint32_t size = 0;
            peer.socket_receive((char*)&size, sizeof(uint32_t));
            size = ntohl(size);
            std::vector<char> buff(size);
            peer.socket_receive(buff.data(), size);
            serializer.deserializer(buff, intention);

            if (intention.up){
                this->snapshot.pos_x += 0.01;
            }
            if (intention.down){
                this->snapshot.pos_y -= 0.01;
            }
            if (intention.angle_right){
                this->snapshot.direction += 0.01;
            }
            if (intention.angle_left){
                this->snapshot.direction -= 0.01;
            }
            if (intention.attack){
                std::cout << "Intencion de ataque" <<std::endl;

                this->action->update_values(this->snapshot.pos_x, this->snapshot.pos_y, this->snapshot.current_weapon);
                //resuelve el modelo
                //action.impact_x; 
                //action.impact_y;

                // msg = serializer.serialize(action);
                // peer.socket_send(&action_id, sizeof(char));
                // uint32_t snap_size = htonl(msg.size());
                // peer.socket_send((char*)&snap_size, sizeof(uint32_t));
                // peer.socket_send(msg.data(), msg.size());

            }

            // msg = serializer.serialize(this->snapshot);
            // // uint32_t aux = msg.size();
            // uint32_t snap_size = htonl(msg.size());
            // // std::cout << "Size htnol: " << std::endl;
            // // for (int i = 0; i < (int)sizeof(uint32_t); i++) {
            // //     printf("%02X ", (unsigned)(unsigned char)((char*)&snap_size)[i]);
            // // }
            // // printf("\n");

            // //MANDO TIPO DE MENSAJE ID
            // peer.socket_send(&snapshot_id, sizeof(char));
            // //MANDO TAMANIO DEL MENSAJE A LEER
            // peer.socket_send((char*)&snap_size, sizeof(uint32_t));
            // //MANDO CADENA BINARIA DEL MENSAJE COMPLETO
            // peer.socket_send(msg.data(), msg.size());

            std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
            unsigned int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
            int sleep_time = 1000000/FPS - elapsed_microseconds;
            if (sleep_time > 0) {
                usleep(1000000/FPS - elapsed_microseconds);
            }else{
            std::cout << "Bajada FPS" << std::endl;
            }
        }
        /*********************************/

        //Player main_player; //Creo un nuevo player a la partida
        //game_play.add_player(main_player);



        //Instanciar un thread para recibir intenciones
        //Instanciarun thread para enviar snapshot.



        //EJEMPLO ENVIO SNAPSHOT
        // Serializer serializer;
        // std::vector <char> msg = serializer.serialize();
        // uint32_t size = htonl(msg.size());
        // peer.socket_send((char*)&size, sizeof(uint32_t));
        // peer.socket_send(msg.data(), size);


        //ESTO DEBERIA IR UNO EN THREAD RECIBIDOR Y OTRO EN EL SENDER
        // while (state){
        //     std::string petition;
        //     size_t read = 0;
        //     while ((read = peer.socket_receive(cmd.data(), CHUNK_SZ)) > 0){
        //         std::string aux(cmd.begin(), cmd.begin()+read);
        //         petition += aux;
        //         std::cout << aux << std::endl;
        //         std::cout << "Leido" << std::endl;
        //     }
        //     //creo un hilo para receive y otro para send
        //     //envio snapshot completa al cliente.
        //     //peer.socket_send(output.c_str(), output.length());
        // }

        dead = true;
        peer.socket_shutdown(SHUT_RDWR);
    }catch(const std::exception& e){
        perror(e.what());
    }catch(...){}
}

ThClient::ThClient(Socket&& socket, GameHandler & game_handler):game_handler(game_handler){
    this->peer = std::move(socket);
        this->snapshot.player_id = 0;
        this->snapshot.pos_x = 2;
        this->snapshot.pos_y = 2;
        this->snapshot.direction = 90;
        this->snapshot.ammo = 100;
        this->snapshot.current_weapon = '0';
        this->action = new Action(this->snapshot.player_id);
}

ThClient::~ThClient(){
    peer.socket_shutdown(SHUT_RDWR);
    delete this->action;
}
