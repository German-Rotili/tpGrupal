#ifndef __SERVER_HELPER_H__
#define __SERVER_HELPER_H__

#include <string>

class Server{
private:
    /* data */
public:
    Server(/* args */);
    ~Server();
    void run(std::string & port, std::string & root);
};



#endif // __SERVER_HELPER_H__