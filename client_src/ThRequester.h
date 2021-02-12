#ifndef TH_REQUESTER
#define TH_REQUESTER
#include "../common_src/common_thread.h"
#include "../common_src/common_socket.h"
#include "../common_src/common_exception.h"
#include "../common_src/Action.h"
#include "../common_src/Snapshot.h"
#include <atomic>
#include "client_helper.h"
#include <mutex>
#define FPS 30


class ThRequester : public Thread{
private:
    Snapshot snapshot;
    std::atomic<bool> state;
    Client & client;
    std::mutex m;
public:
    ThRequester(Client & client);
    ~ThRequester();
    Snapshot get_snapshot();
    void run() override;
    void stop();
    ThRequester(const ThRequester&) = delete;
    ThRequester& operator=(const ThRequester&) = delete;
};
#endif