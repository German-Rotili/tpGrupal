#ifndef SERVER_SERVER
#define SERVER_SERVER
#include <string>

class Server{
private:
    /* data */
public:
    Server(/* args */);
    ~Server();
    void run(std::string & port, std::string & root);
};

#endif
