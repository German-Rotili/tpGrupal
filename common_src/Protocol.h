#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <vector>
#include "common_socket.h"

class Protocol{

private:

    Socket socket;
    
public:
    Protocol();
    explicit Protocol(Socket&& socket);
    ~Protocol();
    Protocol& operator=(const Protocol&) = delete;
    Protocol(const Protocol&) = delete;
    Protocol(Protocol&& other);
    Protocol& operator=(Protocol&& other);
    void send_integer(int & value);
    void send_char(char & value);
    void send_vector_char(std::vector<char> & value);
    void send_vector_int(std::vector<int> & value);
    void send_usernames(std::vector<std::vector<char>> & usernames);
    void send_standard_msg(std::vector<char> & msg);
    std::vector<char> receive_standar_msg();
    char receive_char();
    int receive_int();
};

#endif
