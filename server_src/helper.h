#ifndef __SERVER_HELPER_H__
#define __SERVER_HELPER_H__

#include <string>

class Server{
public:
    Server();
    ~Server();
    void run(std::string & port);
};



#endif // __SERVER_HELPER_H__