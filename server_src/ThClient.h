#ifndef __SERVER_THCLIENT_H__
#define __SERVER_THCLIENT_H__

#include "../common_src/common_socket.h"
//#include "Map.h"
#include "GameHandler.h"
#include "GamePlay.h"
#include "../common_src/common_thread.h"
//#include "Player.h"
#include <vector>
#include <string>
#include <utility>
#include "../common_src/Serializer.h"
#include "ThClientSender.h"
#define CHUNK_SZ 1

class ThClient : public Thread{
private:
    Socket peer;
    Action* action;
    player_t snapshot;
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