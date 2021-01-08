#ifndef __SERVER_THCLIENT_H__
#define __SERVER_THCLIENT_H__

#include "../common_src/common_socket.h"
#include "Map.h"
#include "GameHandler.h"
#include "GamePlay.h"
#include "../common_src/common_thread.h"
#include "player.h"
#include <vector>
#include <string>
#include <utility>
#define CHUNK_SZ 64

class ThClient : public Thread{
private:
    Socket peer;
    bool state = true;
    GameHandler & game_handler;
    ThClient& operator=(const ThClient&) = delete;
    ThClient(const ThClient&) = delete;

public:
    ThClient(Socket&& socket, GameHandler & game_handler);
    ~ThClient();

    /*Recibe, chequea y responde las peticiones*/
    void run() override;

    /*Devuelve el estado del thread*/
    bool is_dead();
};


#endif // __SERVER_THCLIENT_H__