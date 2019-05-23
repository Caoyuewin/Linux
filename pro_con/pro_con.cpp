/*  生产者与消费者模型
 *  1.实现线程安全队列，对外提供线程安全的数据入队和出队
 *  2.创建线程，分别作为生产者与消费者数据入队或数据出队
 *  #include <pthread.h>
 *
 *  int pthread_mutex_destroy(pthread_mutex_t *mutex);
 *  int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrict attr);
 *  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 */



#include <stdio.h>
#include <iostream>
#include <queue>
#include <pthread.h>

using namespace std;

#define MAX_QUEUE 10

class BlockQueue{
  public:
    BlockQueue(int cap = MAX_QUEUE):_capacity(cap){
      pthread_mutex_init(&_mutex, NULL);
      pthread_cond_init(&_cond_con, NULL);
      pthread_cond_init(&_cond_pro, NULL);
    }

    ~BlockQueue(){
      pthread_mutex_destroy(&_mutex);
      pthread_cond_destroy(&_cond_con);
      pthread_cond_destroy(&_cond_pro);

    }
    //入队
    void QueuePush(int data){
      QueueLock();
      while(QueueIsFull()){
        ProWait();
      }
      _queue.push(data);
      ConWakeUp();
      QueueUnlock();
    }
    //出队
    void QueuePop(int *data){
      QueueLock();
      while(QueueIsEmpty()){
        ConWait();
      }
      *data = _queue.front();
      _queue.pop();
      ProWakeUp();
      QueueUnlock();
    }
  private:
    void QueueLock(){
      pthread_mutex_lock(&_mutex);
    }//加锁
    void QueueUnlock(){
      pthread_mutex_unlock(&_mutex);
    }//解锁
    void ConWakeUp(){
      pthread_cond_signal(&_cond_con);
    }//唤醒消费者
    void ConWait(){
      pthread_cond_wait(&_cond_con, &_mutex);
    }//消费者等待
    void ProWait(){
      pthread_cond_wait(&_cond_pro, &_mutex);
    }//生产者等待
    void ProWakeUp(){
      pthread_cond_signal(&_cond_pro);
    }//唤醒生产者
    bool QueueIsFull(){
      return (_capacity == _queue.size());
    }//判断队列是否满了
    bool QueueIsEmpty(){
      return (0 == _queue.size());
    }//判断队列是否为空
  private:
    std::queue<int> _queue;
    int _capacity; //队列节点最大值
    //线程安全实现成员
    pthread_mutex_t _mutex;
    pthread_cond_t _cond_pro;
    pthread_cond_t _cond_con;
};

void* thr_consumer(void* arg){
  BlockQueue *q = (BlockQueue*)arg;
  while(1){
    int data;
    q->QueuePop(&data);
    cout<<"consumer get data:" << data << endl;
  }
  return NULL;
}

int i = 0;
pthread_mutex_t mutex;

void* thr_productor(void* arg){
  BlockQueue *q = (BlockQueue*)arg;
  while(1){
    pthread_mutex_lock(&mutex);
    q->QueuePush(i++);
    cout<< "productor put data:" << i << endl;
    pthread_mutex_unlock(&mutex);
    
  
  }
  return NULL;
}

int main(){
  BlockQueue q;
  pthread_t ctid[4], ptid[4];
  int i, ret;
  pthread_mutex_init(&mutex, NULL);
  for(i = 0; i < 4; i++){
    ret = pthread_create(&ctid[i], NULL, thr_consumer, (void*)&q);
    if(ret != 0){
      cout<<"pthread create error"<<endl;
      return -1;
    }
  }
  for(i = 0; i < 4; i++){
    ret = pthread_create(&ptid[i], NULL, thr_productor, (void*)&q);
    if(ret != 0){
      cout<<"pthread create error"<<endl;
      return -1;
    }

    for(i = 0; i < 4; i++){
      pthread_join(ctid[i], NULL);
    }
    for(i = 0; i < 4; i++){
      pthread_join(ptid[i], NULL);
    }
  }
}
