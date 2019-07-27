#pragma once
#include "tcpsocket.hpp"


class TcpClient{
  public:
    TcpClient(){

    }
    ~TcpClient() {

    }
    bool connect(const std::string& ip, uint16_t port){

    }

    bool Recv(std::string* msg) {

    }

    bool Send(const std::string& msg) {

    }

  private:
    Tcpsocket sock_;
};
