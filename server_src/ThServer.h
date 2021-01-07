#ifndef __SERVER_THSERVER_H__
#define __SERVER_THSERVER_H__


#include <atomic>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include "ThClient.h"
#include "Map.h"
#include "ThClient.h"
#include "GameHandler.h"
#include "../common_src/common_thread.h"
#include "../common_src/common_socket.h"
#include "../common_src/common_exception.h"
#define THREADS_NUM 10


class ThServer : public Thread{
private:
    std::atomic<bool> state;
    std::string & root;
    Socket server;
    Map *map;
    std::vector<Thread*> threads;
    /*Elimina los threads que ya finalizaron su proceso*/
    void clean_clients(std::vector<Thread*> threads);

public:
    ThServer(std::string & port, std::string & root);
    ~ThServer();

    /*Recepciona un socket cliente, asigna una partida
    e inicia el thread.*/
    void run() override;

    /*Cierra el socket de forma violenta*/
    void stop();
    ThServer(const ThServer&) = delete;
    ThServer& operator=(const ThServer&) = delete;
};

#endif // __SERVER_THSERVER_H__