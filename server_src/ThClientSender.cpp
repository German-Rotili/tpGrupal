#include "ThClientSender.h"
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
                this->protocol->send_char(action_id);
                msg = serializer.serialize_action(snapshot);
                this->protocol->send_standard_msg(msg);

                /*****SEND SNAPSHOT****/
                this->protocol->send_char(snapshot_id);
                msg = serializer.serialize_snapshot(snapshot);
                this->protocol->send_standard_msg(msg);
            }
         } catch (std::exception const& e) {
            std::cout << "ThSender Closed ";
            this->dead = true;
        }
        catch (...) {
            this->dead = true;
            std::cout << "Error inesperado ThSender" << std::endl;
        }       
}


void ThClientSender::send_scores(int amount){
            std::cout << "sending scores" << std::endl;

    this->protocol->send_scores(amount);
}
void ThClientSender::send_score( std::vector<char> & username, int score, int kills, int shots ){
            std::cout << "sending score" << std::endl;
    this->protocol->send_score(username, score, kills, shots);
}



ThClientSender::ThClientSender(Protocol *protocol):protocol(protocol),state(true){}

ThClientSender::~ThClientSender(){
    this->snapshots.close_queue();
    this->dead = true;
}

void ThClientSender::stop(){
    this->dead = true;
    this->state = false;
    this->snapshots.close_queue();
}