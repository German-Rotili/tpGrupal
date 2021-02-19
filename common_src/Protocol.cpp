#include "Protocol.h"

Protocol::Protocol(Socket&& socket){
    this->socket = std::move(socket);
}
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
    uint32_t aux = 0;
    this->socket.socket_receive((char*)&aux, sizeof(uint32_t));
    return (int)ntohl(aux);
}

char Protocol::receive_char(){
    char aux = 'x';
    this->socket.socket_receive((char*)&aux, sizeof(char));
    return aux;
}

void Protocol::send_standard_msg(std::vector<char> & msg){
    uint32_t msg_size = htonl(msg.size());
    this->socket.socket_send((char*)&msg_size, sizeof(uint32_t));
    this->socket.socket_send(msg.data(), msg.size());
}

std::vector<char> Protocol::receive_standar_msg(){
    /*Recibo la cantidad de bytes a leer*/
    int size = this->receive_int();
    /************************************/

    /* Recibo el mensaje completo a leer*/
    std::vector<char> msg(size);
    this->socket.socket_receive(msg.data(), size);
    return msg;
    /************************************/
}

void Protocol::send_username(std::vector<char> username){
    int aux = 1;
    this->send_integer(aux);
    this->send_vector_char(username);

}


std::vector<std::string> Protocol::receive_usernames(){
    std::vector<std::string> usernames;
    int size = this->receive_int();
    for(int i = 0; i < (int)size ; i++){
        std::vector<char> user = this->receive_standar_msg();
        user.push_back('\0');
        std::string username(user.data());
        usernames.push_back(username);
    }
    return usernames;
}

void Protocol::send_string_msg(std::string & msg){
    uint32_t msg_size = htonl(msg.length());
    this->socket.socket_send((char*)&msg_size, sizeof(uint32_t));
    this->socket.socket_send(msg.c_str(), msg.length());
}
void Protocol::send_usernames(std::vector<std::vector<char>> & usernames){
    int aux = usernames.size();
    this->send_integer(aux);
    for(std::vector<char> &user : usernames){
        this->send_vector_char(user);
        std::string aux(user.data());
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
    this->socket.socket_send((char*)value.data(), aux);
}


std::vector<int> Protocol::receive_vector_int(){
    int msg_size = this->receive_int();
    std::vector<int> msg;
    for(int i = 0; i < (int)msg_size ; i++){
        int element = this->receive_int();
        msg.push_back(element);
    }
    return msg;
}

void Protocol::send_vector_int(std::vector<int> & value){
    /*Envio la cantidad de elementos del vector*/
    uint32_t size_to_send = htonl(value.size());
    this->socket.socket_send((char*)&size_to_send, sizeof(uint32_t));
    /*******************************************/

    /*******Envio cada elemento del vector *******/
    for(int &element : value){
        size_to_send = htonl(element);
        this->socket.socket_send((char*)&size_to_send, sizeof(int));
    }
    /*******************************************/
}

void Protocol::close(){
    this->socket.socket_shutdown(SHUT_RDWR);
}