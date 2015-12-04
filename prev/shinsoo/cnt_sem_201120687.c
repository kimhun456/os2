#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


#define THREAD_NUM 3
int count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *counter(void *data);

int main(){
  int i,j;
  int status;

  pthread_t pthread[THREAD_NUM];

  for(i=0; i<THREAD_NUM; i++)
    pthread_create(&pthread[i], NULL, counter, (void *)i);

  for(j=0; j<THREAD_NUM; j++)
    pthread_join(pthread[j],NULL);

  return 0;
}


void *counter(void *data){

  int id;
  int i;
  id = (int)data;

  printf("Counter%d is Created!\n",id);

  while(1){

    pthread_mutex_lock(&mutex);

    printf("Counter%d : %d\n", id, count);
    count++;

    pthread_mutex_unlock(&mutex);

    sleep(1);
  }
}
