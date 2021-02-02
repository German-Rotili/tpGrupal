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
#include "../common_src/Serializer.h"
#include <chrono>
#define FPS 30

void ThClient::run(){
    try {
        //acepto un nuevo cliente, tiene que elegir la partida o crear nueva
        //Le mando los id de las partidas que tengo y el id de los mapas para que cree una nueva partida?
        //recibo cantidad de players que va a tener la partida?

                //std::vector<char> cmd(CHUNK_SZ,0);
                //std::string output = game_handler.show_matches();
                //peer.socket_send(output.c_str(), output.length());
                //peer.socket_recieve(output.c_str(), output.length());
                //Parseo la partida que eligio y la asigno al cliente.

        //std::string id;
        //GamePlay game_play = game_handler.select_match(id);
        //or
        //GamePlay game_play = game_handler.new_match();


        /*LECTURA DE ARCHIVO A VECTOR DE CHAR*/
            std::string filename("../editor_src/config/mapa_test.yaml");
            std::vector<char> bytes;
            char byte = 0;
            std::ifstream input_file(filename);
            if (!input_file.is_open()) {
                std::cerr << "Error al abrir mapa" << std::endl;
            }
            while (input_file.get(byte)) {
                bytes.push_back(byte);
            }
            input_file.close();
             
            printf("****************MAP Server*************\n");
            for (int i = 0; i < (int)bytes.size(); i++) {
                printf("%02X ", (unsigned)(unsigned char)bytes.data()[i]);
            }
            printf("*****************************\n");


        /*********************************/


        /*ENVIO DEL MAPA*/
        uint32_t size_1 = htonl(bytes.size());
        peer.socket_send((char*)&size_1, sizeof(uint32_t));
        peer.socket_send(bytes.data(), bytes.size());
        /*********************************/


        /*ENVIO SNAPSHOT DEL JUGADOR*/
        player_t player;
        player.player_id = 10;
        player.pos_x = 2;
        player.pos_y = 2;
        player.direction = 90;
        player.ammo = 100;
        player.current_weapon = '0';
        Serializer serializer;
        std::vector <char> msg = serializer.serialize(player);
        //serializer.deserializer(msg);
        uint32_t snap_size = htonl(msg.size());
        peer.socket_send((char*)&snap_size, sizeof(uint32_t));
        peer.socket_send(msg.data(), msg.size());
        /*********************************/


        intention_t intention;

        /*GAME LOOP*/
        while (state){
            std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

            uint32_t size = 0;
            peer.socket_receive((char*)&size, sizeof(uint32_t));
            size = ntohl(size);
            std::vector<char> buff(size);
            peer.socket_receive(buff.data(), size);
            serializer.deserializer(buff, intention);

            if (intention.up){
                player.pos_x += 0.001;
            }
            if (intention.down){
                player.pos_y += 0.001;
            }
            if (intention.angle_right){
                player.direction += 0.001;
            }

            msg = serializer.serialize(player);
            // uint32_t aux = msg.size();
            uint32_t snap_size = htonl(msg.size());
            // std::cout << "Size htnol: " << std::endl;
            // for (int i = 0; i < (int)sizeof(uint32_t); i++) {
            //     printf("%02X ", (unsigned)(unsigned char)((char*)&snap_size)[i]);
            // }
            // printf("\n");
            peer.socket_send((char*)&snap_size, sizeof(uint32_t));
            peer.socket_send(msg.data(), msg.size());

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
}
