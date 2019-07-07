#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* testcancel(void* arg){
  printf("i am thread testcancel\n");
  pthread_cancel((pthread_t)arg);
  return NULL;
}


void* testexit(void* arg){
  
  int i = 3;
  while(i){
    printf("%d\n", i);
    if(i == 0){
      pthread_exit(NULL);
    }
    sleep(1);
    i--;
  }
  return NULL;
}

int main(){
  pthread_t tid;
  pthread_t tid2;
  int ret;
  int ret2;
  ret = pthread_create(&tid, NULL, testexit, NULL);
  if(ret){
    perror("pthread_create error:");
  }
  ret2 = pthread_create(&tid2, NULL, testcancel, (void*)&tid2);
  pthread_detach(tid2);
  pthread_join(tid, NULL);
  printf("main thread\n");
  return 0;

}
