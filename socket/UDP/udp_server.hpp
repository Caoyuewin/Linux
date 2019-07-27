#pragma once
#include "udp_socket.hpp"
#include <assert.h>
#include <functional>

//通用的Udp服务器类
//1. 根据请求计算响应
//2. 根据请求计算响应
//3.把响应写回到客户端
//其中1,3是固定套路，不管是啥场景，代码都一样
//2是和业务相关，所以把2对应的代码提取成一个回调函数

typedef void (*Handler)(const std::string& req, std::string* resp);
//typedef std::is_function<void(const std::string&, std::string*)> Handler;

class UdpServer{
  public:
    UdpServer() {
      assert(sock_.Socket());
    }

    ~UdpServer() {
      sock_.Close();
    }

    bool Start(const std::string& ip, uint16_t port, Handler handler){
      bool ret = sock_.Bind(ip, port);
      if(!ret) {
        return false;
      }
      while(1) {
        std::string req;
        std::string peer_ip;
        uint16_t peer_port;
        sock_.RecvFrom(&req, &peer_ip, &peer_port);
        std::string resp;
        handler(req,&resp);
        sock_.SendTo(resp,peer_ip, peer_port);
      }
    }

  private:
    UdpSocket sock_;
};
