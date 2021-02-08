#include "ThClient.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
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

        //envio las partidas disponibles.

        //new game(recibe el mapa del cliente)- join game - refresh


        //le mando una referencia de this a la partida.



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





        ThClientSender ThSender(this->peer, this->snapshot);
        ThSender.start();
        Serializer serializer;

        /*GAME LOOP tiene que ir a GAMEPLAY!*/
        while (state){
            std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

            uint32_t size = 0;
            peer.socket_receive((char*)&size, sizeof(uint32_t));
            size = ntohl(size);
            std::vector<char> intention(size);
            peer.socket_receive(intention.data(), size);

            for(char value : intention){
                this->intention_queue.push_back(value);
            }//revisar copiado de value...      

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
}

ThClient::~ThClient(){
    peer.socket_shutdown(SHUT_RDWR);
    delete this->action;
}

void ThClient::send_snapshot(Snapshot snapshot){
    this->snapshot = snapshot;
    //NOTIFY ALL, podria hacerlo en gameplay?
}