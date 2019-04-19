#include<stdio.h>
#include<unistd.h>

int gval = 100;

int main(){
  int ret = fork();
  if(ret < 0){
    printf("fork error\n");
    return -1;
  }
  if(!ret){//子进程进入
    gval = 99;
    printf("https://me.csdn.net/qq_39383636---%d val = %d\n", getpid(), gval);
  }
  else{//父进程进入
    printf("cyw的csdn\n---%d val = %d\n", getpid(), gval);
    sleep(1); 
  }
  printf("%d\n", gval);
  return 0;
}
