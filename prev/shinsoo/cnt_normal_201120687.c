#include <stdio.h>
#include <pthread.h>

#define THREAD_NUM 3
int count = 0;

void *counter(void *data);

int main(){
  int i,j;

  pthread_t pthread[THREAD_NUM];

  for(i=0; i<THREAD_NUM; i++)
    pthread_create(&pthread[i], NULL, counter, (void *)i);

  for(j=0; j<THREAD_NUM; j++)
    pthread_join(pthread[j],NULL);

  return 0;
}


void *counter(void *data){

  id = (int)data;
  int tmp;
  printf("Counter%d is Created!\n",id);

  while(1){

    sleep(1);
    printf("Counter%d : %d\n", id, count);
    count++;

  }

}
