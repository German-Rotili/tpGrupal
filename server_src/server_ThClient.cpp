#include "server_ThClient.h"
#include <string>
#include <vector>

void ThClient::run(){
    try {
        std::vector<char> cmd(CHUNK_SZ,0);

        
        while (state){
            std::string petition;
            size_t read = 0;
            while ((read = peer.socket_receive(cmd.data(), CHUNK_SZ)) > 0){
                std::string aux(cmd.begin(), cmd.begin()+read);
                petition += aux;
            }
            //(*this->map).move_player(player_1, direction);

            //creo un hilo para receive y otro para send
            //envio snapshot completa al cliente.
            //peer.socket_send(output.c_str(), output.length());
        }

        //HttpParser hp(petition, filestore);
        //HttpCMD *http_cmd = hp();
       // std::string output = (*http_cmd).execute();
        //delete http_cmd;
        dead = true;
        peer.socket_shutdown(SHUT_RDWR);
    }catch(const std::exception& e){
        perror(e.what());
    }catch(...){}  
}

ThClient::ThClient(Socket&& socket, Player & player, Map & map):
        player(player), map(map){
    this->peer = std::move(socket);
}

ThClient::~ThClient(){
    peer.socket_shutdown(SHUT_RDWR);
}
