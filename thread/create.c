#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


#if 0
int main(int argc, char* argv[], char* env[]){
  int i = 0;
  while(env[i] != NULL){
    printf("%s\n", env[i]);
    i++;
  }
return 0;

}
#endif

void* th_start(void* arg){
  while(1){
    printf("normal thread---%s\n",(char*)arg);
    sleep(1);
  }
  return NULL;
}


int main(int argc, char* argv[]){
 pthread_t tid;
 int ret;
 char* ptr = "play football";
 ret = pthread_create(&tid, NULL, th_start, ptr);
 if(ret){
   perror("pthread_create error:");
 }
 while(1){
   printf("mainthread id:%p]\n",tid);//tid:线程空间首地址
   sleep(1);
 }
  return 0;
}
