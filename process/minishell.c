//1.获取标准输入中的字符串
//2.对字符串进行解析[ls   -l  -a]
//3.创建子进程
//4.父进程进行进程等待

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>


int main(){
  char buf[1024] = {0};
  while(1){
    printf("[user@localhost]$ ");
    fflush(stdout);
    //scanf("%s", buf);
    //%[^\n]  从缓冲区取数据的时候，遇到\n就停下来
    //经过这一步，缓冲区中留下了一个\n，导致scanf非阻塞
    //%*c  从缓冲区取出一个字符，丢弃这个字符
    //scanf获取的数据放入了几个空间，返回值就是几
    if(scanf("%[^\n]%*c", buf) != 1){
      getchar();
      continue;
    }
    //printf("%s\n", buf);

    int argc = 0;
    char* argv[32];
    char* ptr = buf;
    while(*ptr != '\0'){
      //非空白字符进入判断
      //isspace()
      //return value:如果是空字符返回非零数值，否则返回0
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
    //实现shell的内建命令cd
    if(!strcmp(argv[0], "cd")){
      //int chdir(const char *path)
      //改变当前工作路径
      chdir(argv[1]);
      continue;
    }


    int pid = fork();
    if(pid < 0){
      perror("fork error");
    }
    if(pid == 0) {
      execvp(argv[0], argv);
      exit(-1);
    }
    wait(NULL);
  }
  return 0;
} 
