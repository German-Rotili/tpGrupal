#ifndef __SERVER_THCLIENT_H__
#define __SERVER_THCLIENT_H__

#include "../common_src/common_socket.h"
#include "server_Map.h"
#include "../common_src/common_thread.h"
#include "server_player.h"
#include <vector>
#include <string>
#include <utility>
#define CHUNK_SZ 64

class ThClient : public Thread{
private:
    Socket peer;
    bool state = true;
    Player & player;
    Map & map;
    ThClient& operator=(const ThClient&) = delete;
    ThClient(const ThClient&) = delete;

public:
    ThClient(Socket&& socket, Player & player, Map & map);
    ~ThClient();

    /*Recibe, chequea y responde las peticiones*/
    void run() override;

    /*Devuelve el estado del thread*/
    bool is_dead();
};


#endif // __SERVER_THCLIENT_H__