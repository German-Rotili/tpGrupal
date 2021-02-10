#include "ThSender.h"

void ThSender::send_intention(std::vector<char> & intention){
    std::cout << "send intention" << std::endl;
    client.client_send_intention(intention);
}

ThSender::ThSender(Client & client, std::vector<char> & intention):client(client),intention(intention),state(true){}
   
void ThSender::run(){

    //DEBERIA MANDAR SOLO CUANDO HAY UNA NUEVA INTENCION, NO POR TIEMPO.
    while (this->state) {
        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        send_intention(intention);
        intention.clear();
        //analizar mutex notify all
        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
        unsigned int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        int sleep_time = 1000000/FPS - elapsed_microseconds;
        if (sleep_time > 0) {
            usleep(1000000/FPS - elapsed_microseconds);
        } else {
            printf("Server tarda en responder");
        }
    }
}

void ThSender::stop(){
    this->state = false;
}


ThSender::~ThSender(){}