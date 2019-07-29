#include "tcp_cli.hpp"

int main(int argc, char* argv[]) {
  if(argc != 2){
    printf("Usage ./dict_client [ip]\n");
    return 1;
  }
  TcpClient client;
  int ret = client.connect(argv[1], 9090);
  if(!ret) {
    printf("connect failed!\n");
    return 1;
  }
  while(true){
    //从标准输入读数据
    printf("请输入要查询的单词：");
    fflush(stdout);
    char req[1024] = {0};
    scanf("%s", req);
    std::string resp;
    client.Recv(&resp);
    printf("resp:%s\n",resp.c_str());

  }
}
