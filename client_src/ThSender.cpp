#include "ThSender.h"
#include "../common_src/ConnectionClosedException.h"
void ThSender::send_intention(std::vector<char> & intention){
    client.client_send_intention(intention);
}

ThSender::ThSender(Client & client, BlockingQueueIntention & intention):client(client),intentions(intention),state(true){}

void ThSender::run(){
  try {
    while (this->state) {
        std::cout << "inicio loopsender" << std::endl;
        Intention intention_aux = this->intentions.get_element();
        send_intention(intention_aux.get_intention());
        std::cout << "termino loopsender" << std::endl;
    }
    std::cout << "Salgo del loop sender" << std::endl;
  } catch (std::exception const& e) {
    std::cout << "Hubo una excepción:" << std::endl;
    std::cout << e.what() << std::endl;
    this->dead = true;
  }
  catch (...) {
    std::cout << "Error inesperado en conexion" << std::endl;
  }
}

void ThSender::stop(){
    this->state = false;
}


ThSender::~ThSender(){
  std::cout << "Destruyendo requester" << std::endl;
}
