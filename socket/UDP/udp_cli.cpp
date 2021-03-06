#include<cstdio>
#include<cstring>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(int argc, char* argv[]) {
  //1. 创建socket
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if(sock < 0) {
    perror("socket");
    return 1;
  }
  //客户端一般不要bind
  //客户端只要知道服务端的IP地址和端口号就可以
  //如果客户端bind，其他客户端也可能bind同一个端口号，所以客户端最好让随机分配
  
  //2. 客户端直接发送数据即可
  
  sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);
  server_addr.sin_port = htons(9090);

  while(1) {
    char buf[1024] = {0};
    printf("请输入一段内容：");
    fflush(stdout);
    scanf("%s", buf);
    sendto(sock, buf, strlen(buf), 0, (sockaddr*)&server_addr, sizeof(server_addr));

  //从服务器接收返回结果
  char buf_output[1024] = {0};
  recvfrom(sock, buf_output, sizeof(buf_output),0, NULL, NULL);
  printf("server respond: %s\n", buf_output);
  }
  return 0;
}
