#ifndef __THCLIENTSENDER_
#define  __THCLIENTSENDER_


#define FPS_SENDER 30

class ThClientSender : public Thread{
    Socket & peer;
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
