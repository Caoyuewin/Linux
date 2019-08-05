#include "tcpsocket.hpp"
#include <functional>

#define CHECK_RET(exp) if(!(exp)) {\
    return false;\
}

typedef std::function<void (const std::string&, std::string*)> Handler;

class TcpServer{
    public:
        TcpServer(){}
        bool Start(const std::string& ip, uint16_t port, Handler handler){
            //创建一个socket
            CHECK_RET(listen_sock_.Socket());
            //绑定端口号
            CHECK_RET(listen_sock_.Bind(ip, port));
            //进行监听
            CHECK_RET(listen_sock_.Listen());
            printf("Server start OK\n");
            //进入主循环
            while(true){
                //获取一个连接
                Tcpsocket client_sock;
                std::string ip;
                uint16_t port;
                bool ret = listen_sock_.Accept(&client_sock, &ip, &port);
                if(!ret) 
                {
                    continue;
                }
                printf("[%s:%d] 有客户端连接!\n", ip.c_str(), port);
                //和客户端进行具体的沟通
                while(true) {
                    //读取请求
                    std::string req;
                    int r = client_sock.Recv(&req);
                    if(r < 0) {
                        continue;
                    }
                    if(r == 0) {
                        client_sock.Close();
                        printf("[%s:%d] 对端关闭了连接\n", ip.c_str(), port);
                        break;
                    }
                    printf("[%s:%d] 客户端发送了：%s\n", ip.c_str(), port, req.c_str());
                    //根据请求计算响应
                    std::string resp;
                    handler(req, &resp);
                    //把响应写会客户端
                    client_sock.Send(resp);
                    printf("[%s:%d] req :%s, resp:%s\n", ip.c_str(), port, req.c_str(), resp.c_str());
                }
            }
            return true;
        }

    private:
        Tcpsocket listen_sock_;
};
