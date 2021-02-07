#include "ThClientSender.h"



void ThClientSender::run(){
    try {






   /*************   AHORA VIENE DESDE EL CLIENTE!!  ********************/

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
                            
                            // printf("****************MAP Server*************\n");
                            // for (int i = 0; i < (int)bytes.size(); i++) {
                            //     printf("%02X ", (unsigned)(unsigned char)bytes.data()[i]);
                            // }
                            // printf("*****************************\n");
                        /*ENVIO DEL MAPA*/
                        uint32_t size_1 = htonl(bytes.size()+1);
                        peer.socket_send((char*)&size_1, sizeof(uint32_t));
                        peer.socket_send(bytes.data(), bytes.size()+1);
        /******************************************************************/


        char action_id = '1';
        char snapshot_id = '0';
        Serializer serializer;
        std::vector <char> msg;

        /*Constant Sender, hay race condition con el snapshot y hasta con el Action*/
        while (state){
            std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
            //NOTIFY ALL
            if(this->action.active()){
                std::cout << "Accion activa se manda" <<std::endl;

                // action.update_values(this->snapshot.pos_x,this->snapshot.pos_y,this->snapshot.current_weapon);
                std::vector <char> msg = serializer.serialize(action);
                peer.socket_send(&action_id, sizeof(char));
                uint32_t snap_size = htonl(msg.size());
                peer.socket_send((char*)&snap_size, sizeof(uint32_t));
                peer.socket_send(msg.data(), msg.size());
                this->action.update_state(false);
            }

            msg = serializer.serialize(this->snapshot);
            uint32_t snap_size = htonl(msg.size());

            //MANDO TIPO DE MENSAJE ID
            peer.socket_send(&snapshot_id, sizeof(char));
            //MANDO TAMANIO DEL MENSAJE A LEER
            peer.socket_send((char*)&snap_size, sizeof(uint32_t));
            //MANDO CADENA BINARIA DEL MENSAJE COMPLETO
            peer.socket_send(msg.data(), msg.size());

            std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
            unsigned int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
            int sleep_time = 1000000/FPS_SENDER - elapsed_microseconds;
            if (sleep_time > 0) {
                usleep(1000000/FPS_SENDER - elapsed_microseconds);
            }else{
            std::cout << "Bajada FPS" << std::endl;
            }
        }
       

        dead = true;
    }catch(const std::exception& e){
        perror(e.what());
    }catch(...){}
}

ThClientSender::ThClientSender(Socket& socket, Action & action, player_t & snapshot):
    peer(socket),action(action),snapshot(snapshot),state(true){}

ThClientSender::~ThClientSender(){
    this->state = false;
}
