#ifndef __THCLIENTSENDER_
#define  __THCLIENTSENDER_
#include "../common_src/common_socket.h"
#include "../common_src/common_thread.h"
#include "ThClient.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <iterator>
#include "../common_src/Action.h"
#include "../common_src/Snapshot.h"
#include "../common_src/Serializer.h"
#include <atomic>
#include <chrono>
#include "Constants.h"

class ThClientSender : public Thread{
    Socket & peer;
    Snapshot snapshot;
    std::atomic<bool> state;
    ThClientSender& operator=(const ThClientSender&) = delete;
    ThClientSender(const ThClientSender&) = delete;

public:
    ThClientSender(Socket& socket);

    void send_snapshot(Snapshot & snapshot);

    ~ThClientSender();

    void run() override;

    /*Devuelve el estado del thread*/
    bool is_dead();
};

#endif
