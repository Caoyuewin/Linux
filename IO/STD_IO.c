/*
 *标注库IO接口
 * */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
  char* file = "./test.txt";
  FILE* fp = fopen(file,"w+");
  if(fp == NULL){
    perror("fopen error");
    return -1;

  }
  char buf[10] = "hahaha";
  fwrite(buf, strlen(buf), 1, fp);
  fseek(fp,strlen(buf), SEEK_SET);
  fwrite(buf, strlen(buf), 1, fp);
  fclose(fp);



  return 0;
}
