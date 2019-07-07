#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


int main(){
  //1.创建套接字
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if(sock < 0){
    perror("socket");
    return 1;
  }
  //2.绑定IP和端口
  sockaddr_in addr;
  addr.sin_family = AF_INET;//使用IPV4协议
  addr.sin_addr.s_addr = inet_addr("0.0.0.0");//关联所有IP地址
  addr.sin_port = htons(9090);//把主机字节序转成网络字节序，inet_addr内部自带转换功能
  int ret = bind(sock, (sockaddr*)&addr, sizeof(addr));
  if(ret < 0){
    perror("bind");
    return 1;
  }
  printf("server start ok!\n");//绑定成功
  //3.处理请求
  //服务器基本工作流程
  //1.初始化（服务器启动）
  //2.进入主循环（死循环）
  //  a)读取客户端发来的请求(request)
  //  b)根据请求内容，计算生成响应（response）
  //  c)把响应数据返回给客户端
  //回显服务器：客户端发什么，服务端就返回什么
  while(1) {
    sockaddr_in peer;
    socklen_t len = sizeof(peer);//输入输出参数
    char buf[1024] = {0};
    ssize_t n = recvfrom(sock, buf, sizeof(buf) - 1, 0, (sockaddr*)&peer, &len);//面向数据报接口
    if(n < 0) {
      perror("recvfrom");
      continue;
    }
    buf[n] = '\0';
    //echo server请求和响应相同
    n = sendto(sock, buf, strlen(buf), 0, (sockaddr*)&peer, len);
    if(n < 0) {
      perror("sendto");
      continue;
    }
    printf("[%s:%d] buf: %s\n", inet_ntoa(peer.sin_addr), ntohs(peer.sin_port),buf);

  }
  close(sock);
  return 0;
}
