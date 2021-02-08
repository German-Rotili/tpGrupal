#include "client_helper.h"
#define SNAPSHOT_ID '0'
#define ACTION_ID '1'

Client::Client(std::string & service,std::string & hostname){
    this->client.socket_connect(service.c_str(), hostname.c_str());
}

Client::~Client(){}

void Client::client_send(std::string line){
//    client.socket_send(line);
    client.socket_send(line.c_str(), 4);
}


void Client::recieve_snapshot(Snapshot & snapshot){
    
    /*Recibo ID*/
    char input_id;
    std::vector<char> buff(1);
    client.socket_receive(buff.data(), sizeof(char));
    memcpy(&input_id, buff.data(), sizeof(char));
    /**********/


    /*Recibimos vector de chars*/
    std::vector<char> msg = this->client_receive_vector(); //aca adentro primero recibe largo y despues lee todo.
    /**********/
    

    /********/
    Serializer serializer;
    /**********/

    switch (input_id){

        case SNAPSHOT_ID:
            serializer.deserializer(msg, snapshot);
            break;
        
        case ACTION_ID:
            serializer.deserialize_action(msg, snapshot);
            break;

        default:
            std::cout << "Error id detection" <<std::endl;
    } 


}



void Client::client_send_intention(std::vector<char> & intention){
        Serializer serializer;
        uint32_t snap_size = htonl(intention.size());
        client.socket_send((char*)&snap_size, sizeof(uint32_t));
        client.socket_send(intention.data(), intention.size());
}


std::vector<char> Client::client_receive_vector(){

  
    uint32_t size = 0;
    client.socket_receive((char*)&size, sizeof(uint32_t));

 
    size = ntohl(size);
    std::vector<char> buff(size);
    client.socket_receive(buff.data(), size);

   
    // std::cout << "vector size after filled: " << buff.size() <<std::endl;
    // for(int i=0 ; i < buff.size(); i ++){
    //     printf("%02X ", (unsigned)(unsigned char)buff.data()[i]);
    // }
    // printf("\n");
    return buff;
}

std::string Client::client_receive_string(){
    uint32_t size = 0;
    client.socket_receive((char*)&size, sizeof(uint32_t));
    size = ntohl(size);
    // std::cout << "recibi el tamanio a leer: " << size <<std::endl;
    std::vector <char> msg(size);
    client.socket_receive(msg.data(), size);
    // std::cout << "recibi el vector "<<std::endl;

            // printf("****************MAP CLIENT*************\n");
            // for (int i = 0; i < msg.size(); i++) {
            //     printf("%02X ", (unsigned)(unsigned char)msg.data()[i]);
            // }
            // printf("*****************************\n");



    //aca puede haber algo raro
    std::string val(msg.data());
    return val;
}

void Client::run(){
    //client_send();
    //client_receive();
}
