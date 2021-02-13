#include "ThClientSender.h"

void ThClientSender::send_snapshot(Snapshot & snapshot){
    std::unique_lock<std::mutex> lock(m);
    this->snapshot = snapshot;
    cond_var.notify_all();//LLEGO UNA NUEVA SNAPSHOT PARA ENVIAR, NOTIFICO.
}

void ThClientSender::run(){
        while (true){
            std::unique_lock<std::mutex> lock(m); //LOCK PARA EVITAR RACE CONDITION CON
                                                  // EL METODO SEND SNAPSHOT QUE COPIA EL SNAPSHOT

            char action_id = ACTION_ID;
            char snapshot_id = SNAP_ID;
            Serializer serializer;
            std::vector <char> msg;

            /*****SEND ACTIONS****/
            
            //MANDO TIPO DE MENSAJE ID
            peer.socket_send(&action_id, sizeof(char));
            //MANDO TAMANIO DEL MENSAJE A LEER
            msg = serializer.serialize_action(snapshot);
            uint32_t snap_size = htonl(msg.size());
            peer.socket_send((char*)&snap_size, sizeof(uint32_t));
            //MANDO CADENA BINARIA DE LAS ACCIONES
            peer.socket_send(msg.data(), msg.size());
            /********************/


            /*****SEND SNAPSHOT****/

            //MANDO TIPO DE MENSAJE ID
            peer.socket_send(&snapshot_id, sizeof(char));
            //MANDO TAMANIO DEL MENSAJE A LEER
            msg = serializer.serialize_snapshot(snapshot);
            snap_size = htonl(msg.size());
            peer.socket_send((char*)&snap_size, sizeof(uint32_t));
            //MANDO CADENA BINARIA DEL SNAPSHOT COMPLETO
            peer.socket_send(msg.data(), msg.size());
            /********************/

            cond_var.wait(lock);//CUANDO ESTA LISTA LA NUEVA SNAPSHOT ME HACEN NOTIFY ALL

        }

}

ThClientSender::ThClientSender(Socket& socket):
    peer(socket),state(true){}

ThClientSender::~ThClientSender(){
    this->state = false;
}
