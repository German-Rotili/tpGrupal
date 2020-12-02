#ifndef THSERVER_H
#define THSERVER_H
#include <atomic>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include "server_ThClient.h"
#include "server_map.h"
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
#endif
