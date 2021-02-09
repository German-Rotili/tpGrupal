#include "ThClientSender.h"

void ThClientSender::send_snapshot(Snapshot & snapshot){

        char action_id = '1';
        char snapshot_id = '0';//DEFINIR EN CONSTANTES
        Serializer serializer;
        std::vector <char> msg;

            /*****SEND ACTIONS****/
            msg = serializer.serialize_action(snapshot);
            //MANDO TIPO DE MENSAJE ID
            peer.socket_send(&action_id, sizeof(char));
            //MANDO TAMANIO DEL MENSAJE A LEER
            uint32_t snap_size = htonl(msg.size());
            peer.socket_send((char*)&snap_size, sizeof(uint32_t));
            //MANDO CADENA BINARIA DEL MENSAJE COMPLETO
            peer.socket_send(msg.data(), msg.size());
            /********************/


            /*****SEND SNAPSHOT****/
            msg = serializer.serialize_snapshot(snapshot);
            //MANDO TIPO DE MENSAJE ID
            peer.socket_send(&snapshot_id, sizeof(char));
            //MANDO TAMANIO DEL MENSAJE A LEER
            snap_size = htonl(msg.size());
            peer.socket_send((char*)&snap_size, sizeof(uint32_t));
            //MANDO CADENA BINARIA DEL MENSAJE COMPLETO
            peer.socket_send(msg.data(), msg.size());
            /********************/
}

void ThClientSender::run(){
  //usar notify all desde send snapshot y que el snapshot lo mande aca?
}

ThClientSender::ThClientSender(Socket& socket):
    peer(socket),state(true){}

ThClientSender::~ThClientSender(){
    this->state = false;
}
