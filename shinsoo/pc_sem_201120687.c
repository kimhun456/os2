#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 4
#define BUFFER_SIZE 5
#define PRODUCER_NUM 2

typedef int item;

int count = 0;
int in = 0;
int out = 0;

item buff[BUFFER_SIZE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t full;
sem_t empty;
//sem_t mutex;

void *producer();
void *consumer();

int main(){

  int i;

  pthread_t pthread[THREAD_NUM];

  sem_init(&full,0,0);
  sem_init(&empty,0,BUFFER_SIZE-1);
  //sem_init(&mutex,0,1);

  for(i=0;i<PRODUCER_NUM;i++){
    pthread_create(&pthread[i],NULL,producer,NULL);
  }
  for(i=PRODUCER_NUM;i<THREAD_NUM;i++){
    pthread_create(&pthread[i],NULL,consumer,NULL);
  }


  for(i=0;i<THREAD_NUM;i++){
    pthread_join(pthread[i],NULL);
  }

  return 0;
}



void *producer(){

  item next_Produced;
  int temp;

  printf("Producer is Created!\n");

  while(1){

    next_Produced++;

    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    //sem_wait(&mutex);

    buff[in] = next_Produced;
    in = (in+1) % BUFFER_SIZE;

    sleep(1);

    temp = count;
    printf("producer produced, counter : %d -> %d\n", temp, temp+1);
    //next_Produced++;
    count++;

    pthread_mutex_unlock(&mutex);
    //sem_post(&mutex);
    sem_post(&full);

  }

}


void *consumer(){

  item next_Consumed;
  int temp;

  printf("Consumer is Created!\n");

  while(1){

    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    //sem_wait(&mutex);

    next_Consumed = buff[out];
    out = (out+1) % BUFFER_SIZE;

    sleep(1);

    temp = count;
    printf("consumer consumed, counter : %d -> %d\n", temp, temp-1);
    //count--;

    pthread_mutex_unlock(&mutex);
    //sem_post(&mutex);
    sem_post(&empty);

    count--;
  }
}
