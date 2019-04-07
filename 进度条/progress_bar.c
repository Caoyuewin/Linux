#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
  int i = 0;
  int j = 0;
  for (i = 1; i <= 100; i++){
    printf("[%d]",i);
    for(j = 1; j <= i; j++){
     printf("\e[1;%dm*\e[0m", 30 + i % 7);
     fflush(stdout);
    }
    usleep(100000);
    printf("\r");
  }
  printf("\n");
  return 0;
}
/*
int main(){
  int i = 0;
  int j = 0;
  for (i = 1; i <= 100; i++){
    printf("[%d]",i);
    for(j = 1; j <= i; j++){
     printf("\e[1;36m*\e[0m");
     fflush(stdout);
    }
    usleep(100000);
    printf("\r");
  }
  printf("\n");
  return 0;
}
*/var
