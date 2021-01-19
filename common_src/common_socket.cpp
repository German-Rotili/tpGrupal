#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include "common_socket.h"
#include "common_exception.h"
#include "common_socket_exception.h"

Socket::Socket():fd(-1){}

Socket::~Socket(){
  fd == -1 ? 0 : close(fd);
}

Socket::Socket(Socket&& other){
  fd = other.fd;
  other.fd = -1;
}

Socket& Socket::operator=(Socket&& other) {
  this->fd = other.fd;
  other.fd = -1;
  return *this;
}

int Socket::socket_bind(const char *service){
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  std::memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  if (getaddrinfo(NULL,service, &hints, &result) != 0)
    throw SuperException("GetAddr Error en socket bind");

  for (rp = result; rp != NULL; rp = rp->ai_next){
    fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (fd == -1) continue;
    if (bind(fd, rp->ai_addr, rp->ai_addrlen) == 0){
      freeaddrinfo(result);
      return 0;
    }
    close(fd);
  }
  freeaddrinfo(result);
  throw SuperException("Bind Error en socket bind");
}

void Socket::socket_reuse(){
  int enable = 1;
  setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
}

int Socket::socket_listen(const int length){
  return listen(fd, length);
}

void Socket::socket_accept(Socket & peer){
  struct sockaddr client_address;
  socklen_t client_address_length = sizeof(client_address);
  peer.fd = accept(fd, &client_address,
    &client_address_length);
  if (peer.fd < 0){
    throw CloseSocketException();
  }
}

int Socket::socket_connect(const char *service, const char *hostname){
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  std::memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  if (getaddrinfo(hostname,service, &hints, &result) != 0)
    throw SuperException("GetAddr Error en socket connect");

  for (rp = result; rp != NULL; rp = rp->ai_next){
    fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (fd == -1) continue;
    if (connect(fd, rp->ai_addr, rp->ai_addrlen) == 0){
      freeaddrinfo(result);
      return 0;
    }
    close(fd);
  }
  freeaddrinfo(result);
  throw SuperException("Connect Error en socket connect");
}

void Socket::socket_shutdown(int flags){
  shutdown(fd, flags);
  flags == SHUT_RDWR ? close(fd) : 0;
}

void Socket::socket_receive(std::string & response){
  int received = 1;
  char buffer[BUFF_SIZE];
  while (received > 0) {
    received = recv(this->fd, buffer, BUFF_SIZE, 0);
    if (received > 0)
      response.append(buffer, received);
    if (received < 0)
      throw SuperException("Error al recibir bytes en el socket");
  }
}

void Socket::socket_send(std::string & message){
  int total_sent = 0;
  int lenght = message.length();
  while (total_sent < lenght) {
    int sent = send(this->fd, message.substr(total_sent).c_str(),
                    lenght - total_sent, MSG_CONFIRM);
    if (sent == -1) {
      throw SuperException("Error al enviar");
    }
    total_sent += sent;
  }
}
