#pragma once

#include <functional>
#include "tcpsocket.hpp"

typedef std::function<void (const std::string&,std::string*)> Handler;


class TcpProcessServer{
  public:
    TcpProcessServer(){}

    ~TcpProcessServer(){
      listen_sock.close();
    }

    bool Start(const std:;string& ip, uint16_t port, Handler handler){

    }
    
  private:
    TcpSocket listen_sock_;
};
