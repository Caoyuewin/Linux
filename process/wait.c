#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>



int main() {
  int pid;
  pid = fork();
  if(pid < 0) {
    perror("fork:");
    exit(-1);
  }
  else if(pid == 0){
    printf("i am child\n");
    sleep(5);
    exit(99);
  }
  //父进程
  wait(NULL);
  printf("stop wait\n");
  return 0;

}
