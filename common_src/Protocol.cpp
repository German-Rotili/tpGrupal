#include "Protocol.h"

Protocol::Protocol(Socket&& socket){}
Protocol::Protocol(){}
Protocol::Protocol(Protocol&& other){
  this->socket = std::move(other.socket);
}

Protocol& Protocol::operator=(Protocol&& other) {
  this->socket = std::move(other.socket);
  return *this;
}

Protocol::~Protocol(){
    this->socket.socket_shutdown(SHUT_RDWR);
}

int Protocol::receive_int(){
    uint32_t integer = 0;
    this->socket.socket_receive((char*)&integer, sizeof(uint32_t));
    return (int)ntohl(integer);
}

char Protocol::receive_char(){
    char aux = '0';
    this->socket.socket_receive((char*)&aux, sizeof(uint32_t));
    return aux;
}

void Protocol::send_standard_msg(std::vector<char> & msg){
    uint32_t msg_size = htonl(msg.size());
    this->socket.socket_send((char*)&msg_size, sizeof(uint32_t));
    this->socket.socket_send(msg.data(), msg.size());
}

std::vector<char> Protocol::receive_standar_msg(){
    /*Recibo la cantidad de bytes a leer*/
    uint32_t size = 0;
    this->socket.socket_receive((char*)&size, sizeof(uint32_t));
    size = ntohl(size);
    /************************************/

    /* Recibo el mensaje completo a leer*/
    std::vector<char> msg(size);
    this->socket.socket_receive(msg.data(), size);
    return msg;
    /************************************/
}

void Protocol::send_usernames(std::vector<std::vector<char>> & usernames){
    int aux = usernames.size();
    this->send_integer(aux);
    for(std::vector<char> &user : usernames){
        this->send_vector_char(user);
    }
}

void Protocol::send_char(char & value){
    this->socket.socket_send(&value, sizeof(char));
}

void Protocol::send_integer(int & value){
    uint32_t integer = htonl(value);
    this->socket.socket_send((char*)&integer, sizeof(uint32_t));
}
void Protocol::send_vector_char(std::vector<char> & value){
    int aux = value.size();
    this->send_integer(aux);
    this->socket.socket_send((char*)value.data(), value.size());
}

void Protocol::send_vector_int(std::vector<int> & value){
    /*Envio la cantidad de elementos del vector*/
    uint32_t size_to_send = htonl(value.size());
    this->socket.socket_send((char*)&size_to_send, sizeof(uint32_t));
    /*******************************************/

    /*******Envio cada elemento del vecto *******/
    for(int &element : value){
        size_to_send = htonl(element);
        this->socket.socket_send((char*)&value, sizeof(int));
    }
    /*******************************************/
}