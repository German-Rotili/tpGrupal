#ifndef __THCLIENTSENDER_
#define  __THCLIENTSENDER_
#include "../common_src/common_socket.h"
#include "../common_src/Protocol.h"
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
#include "../common_src/BlockingQueueSnapshot.h"
#include <atomic>
#include <chrono>
#include "Constants.h"
#include <condition_variable>

class ThClientSender : public Thread{
    Protocol & protocol;
    BlockingQueueSnapshot snapshots;
    std::atomic<bool> state;
    ThClientSender& operator=(const ThClientSender&) = delete;
    ThClientSender(const ThClientSender&) = delete;

public:
    ThClientSender(Protocol& protocol);

    void send_snapshot(Snapshot & snapshot);

    ~ThClientSender();

    void run() override;
    void stop();
    // bool is_dead();
    friend class GamePlay;
};

#endif
