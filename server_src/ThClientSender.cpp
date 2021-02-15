#include "ThClientSender.h"

void ThClientSender::run(){
        Serializer serializer;
        std::vector <char> msg;
        while (true){
            Snapshot snapshot = this->snapshots->get_element();
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
}

ThClientSender::ThClientSender(Protocol& protocol, BlockingQueueSnapshot *snapshots):
    protocol(protocol),snapshots(snapshots),state(true){}

ThClientSender::~ThClientSender(){
    this->state = false;
}
