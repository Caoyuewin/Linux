#include<stdio.h>
#include<unistd.h>

int main(){
  int i = 0;
  int j = 0;
  for (i = 1; i <= 100; i++){
      printf("[%d]", i);
    for (j = 1; j <= i; j++){
      printf("*");
      fflush(stdout);
    }
    usleep(100000);
    printf("\r");
  }
  printf("\n");
  return 0;

}

