#include "ThClientSender.h"
#include "IdMaker.h"
void ThClientSender::run(){
        Serializer serializer;
        std::vector <char> msg;
        try{
            while (this->state){
                Snapshot snapshot = this->snapshots.get_element();
                // snapshot.print();
                char action_id = ACTION_ID;
                char snapshot_id = SNAP_ID;

                /*****SEND ACTIONS****/            
                this->protocol.send_char(action_id);
                msg = serializer.serialize_action(snapshot);
                this->protocol.send_standard_msg(msg);

                /*****SEND SNAPSHOT****/
                this->protocol.send_char(snapshot_id);
                msg = serializer.serialize_snapshot(snapshot);
                this->protocol.send_standard_msg(msg);
            }
         } catch (std::exception const& e) {
            std::cout << "Hubo una excepción:" << std::endl;
            std::cout << e.what() << std::endl;
            this->dead = true;
        }
        catch (...) {
            this->dead = true;
            std::cout << "Error inesperado en conexion" << std::endl;
        }       
}

ThClientSender::ThClientSender(Protocol& protocol):
    protocol(protocol),state(true){
    IdMaker *IdMaker = IdMaker::GetInstance();
    }

ThClientSender::~ThClientSender(){
}

void ThClientSender::stop(){
    this->state = false;
    this->snapshots.close_queue();
}