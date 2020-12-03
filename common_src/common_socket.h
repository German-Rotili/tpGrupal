#ifndef SOCKET_H
#define SOCKET_H
#define BUFF_SIZE 32
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

class Socket{
public:
  int fd;
  Socket();
  ~Socket();
  Socket& operator=(const Socket&) = delete;
  Socket(const Socket&) = delete;
  int socket_bind(const char *service);
  void socket_reuse();
  int socket_listen(const int length);
  void socket_accept(Socket & peer);
  int socket_connect(const char *service, const char *hostname);
  void socket_shutdown(int flags);
  int socket_receive(char *buffer, int length);
  int socket_send(const char *buffer, int length);
  Socket(Socket&& other);
  Socket& operator=(Socket&& other);
};

#endif
