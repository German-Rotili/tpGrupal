#ifndef TH_REQUESTER
#define TH_REQUESTER
#include "../common_src/common_thread.h"
#include "../common_src/common_socket.h"
#include "../common_src/common_exception.h"
#include "../common_src/ProtectedQueueAction.h"
#include "../common_src/Action.h"
#include "../common_src/Snapshot.h"
#include <atomic>
#include "client_helper.h"
#include <mutex>
#define FPS 30

#define INVALID_ID -9999

class ThRequester : public Thread{
private:
    Snapshot snapshot;
    std::atomic<bool> state;
    std::atomic<int> obtainedId;
    Client & client;
    std::mutex m;
    ProtectedQueueAction & actions;
public:
    ThRequester(Client & client, ProtectedQueueAction & actions);
    ~ThRequester();
    Snapshot get_snapshot();
    int getObtainedId();
    void run() override;
    void stop();
    ThRequester(const ThRequester&) = delete;
    ThRequester& operator=(const ThRequester&) = delete;
    bool is_active();

};
#endif
