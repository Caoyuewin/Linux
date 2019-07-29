#pragma once
#include "tcpsocket.hpp"


class TcpClient{
  public:
    TcpClient(){
      sock_.Socket();
    }
    ~TcpClient() {
      sock_.Close(); 
    }
    bool connect(const std::string& ip, uint16_t port){
      return sock_.connnect(ip,port);
    }

    bool Recv(std::string* msg) {
      return sock_.Recv(msg);
    }

    bool Send(const std::string& msg) {
      return sock_.Send(msg);
    }

  private:
    Tcpsocket sock_;
};
