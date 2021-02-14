#include "ThClientSender.h"

void ThClientSender::send_snapshot(Snapshot & snapshot){
    std::unique_lock<std::mutex> lock(m);
    this->snapshot = snapshot;
    cond_var.notify_all();//LLEGO UNA NUEVA SNAPSHOT PARA ENVIAR, NOTIFICO.
}

void ThClientSender::run(){
        Serializer serializer;
        std::vector <char> msg;
        while (true){
            std::unique_lock<std::mutex> lock(m); //LOCK PARA EVITAR RACE CONDITION CON
                                                  // EL METODO SEND SNAPSHOT QUE COPIA EL SNAPSHOT
            char action_id = ACTION_ID;
            char snapshot_id = SNAP_ID;

            /*****SEND ACTIONS****/            
            //MANDO TIPO DE MENSAJE ID
            this->protocol.send_char(action_id);
            msg = serializer.serialize_action(snapshot);
            this->protocol.send_standard_msg(msg);
            /********************/


            /*****SEND SNAPSHOT****/
            //MANDO TIPO DE MENSAJE ID
            this->protocol.send_char(snapshot_id);
            msg = serializer.serialize_snapshot(snapshot);
            this->protocol.send_standard_msg(msg);
            /********************/

            cond_var.wait(lock);//CUANDO ESTA LISTA LA NUEVA SNAPSHOT ME HACEN NOTIFY ALL

        }

}

ThClientSender::ThClientSender(Protocol& protocol):
    protocol(protocol),state(true){}

ThClientSender::~ThClientSender(){
    this->state = false;
}
