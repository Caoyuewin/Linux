#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


int main(){
  char buf[1024] = {0};
  while(1){
    printf("[user@localhost]$ ");
    fflush(stdout);
    //scanf("%s", buf);
    //%[^\n]  从缓冲区取数据的时候，遇到\n就停下来
    //经过这一步，缓冲区中留下了一个\n，导致scanf非阻塞
    //%*c  从缓冲区取出一个字符，丢弃这个字符
    if(scanf("%[^\n]%*c", buf) != 1){
      getchar();
    }
    printf("%s\n", buf);

    int argc = 0;
    char* argv[32];
    char* ptr = buf;
    while(*ptr != '\0'){
      //非空白字符进入判断
      if(!isspace(*ptr)){
        argv[argc] = ptr;
        argc++;
        while(!isspace(*ptr) && *ptr != '\0'){
          ptr++;
        }
        *ptr = '\0';
        //printf("argv[%d] = [%s]\n", argc, argv[argc - 1]);
      }
      ptr++;
    }
    argv[argc] = NULL; //程序替换的最后一个参数要是NULL;
    int pid = fork();
    if(pid < 0){
      perror("fork error");

    }
  }
  return 0;
} 
