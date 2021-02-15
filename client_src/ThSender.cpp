#include "ThSender.h"

void ThSender::send_intention(std::vector<char> & intention){
    client.client_send_intention(intention);
}

ThSender::ThSender(Client & client, BlockingQueueIntention & intention):client(client),intentions(intention),state(true){}
   
void ThSender::run(){

    while (this->state) {
        Intention intention_aux = this->intentions.get_element();
        send_intention(intention_aux.get_intention());
    }
}

void ThSender::stop(){
    this->state = false;
}


ThSender::~ThSender(){}