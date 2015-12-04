#include <stdio.h>
#include <pthread.h>

#define THREAD_NUM 4
#define BUFFER_SIZE 5
#define PRODUCER_NUM 2

typedef int item;

int count = 0;
int in = 0;
int out = 0;

item buff[BUFFER_SIZE];


void *producer();
void *consumer();


int main(){

  int i;

  pthread_t pthread[THREAD_NUM];

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

  while(1){

    while(((in+1) % BUFFER_SIZE) == out);

    buff[in] = next_Produced;
    in = (in+1) % BUFFER_SIZE;

    sleep(1);

    temp = count;
    printf("producer produced, counter : %d -> %d\n", temp, temp+1);
    next_Produced++;
    count++;

  }

}


void *consumer(){

  item next_Consumed;
  int temp;

  while(1){

    while(in==out);

    next_Consumed = buff[out];
    out = (out+1) % BUFFER_SIZE;

    sleep(1);

    temp = count;
    printf("consumer consumed, counter : %d -> %d\n", temp, temp-1);
    count--;
  }
}
