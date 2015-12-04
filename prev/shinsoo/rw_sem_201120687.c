#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 5
#define READER_NUM 2
#define WRITER_NUM 3


int count = 0;
int reader_count = 0;

sem_t rw_mutex;
sem_t mutex;


void *reader(void *data);
void *writer(void *data);



int main(){

  int i;

  pthread_t pthread[THREAD_NUM];

  sem_init(&rw_mutex, 0, 1);
  sem_init(&mutex, 0, 1);

  for(i=0;i<READER_NUM;i++){
    pthread_create(&pthread[i],NULL,reader,(void*)i);
  }
  for(i=READER_NUM;i<THREAD_NUM;i++){
    pthread_create(&pthread[i],NULL,writer,(void*)i);
  }

  for(i=0;i<THREAD_NUM;i++){
    pthread_join(pthread[i],NULL);
  }

  return 0;
}



void *reader(void *data){

  int id = (int)data;
  int temp;

  //printf("Reader%d is reading the data\n",id);

  while(1){

    sem_wait(&mutex);
    reader_count++;

    if(reader_count == 1) sem_wait(&rw_mutex);

    sem_post(&mutex);

    printf("Reader%d reads Count : %d\n", id, count);


    sem_wait(&mutex);
    reader_count--;

    if(reader_count == 0) sem_post(&rw_mutex);
    sem_post(&mutex);

    sleep(1);

  }

}


void *writer(void *data){

  int id = (int)data;
  int temp;

  while(1){

    sem_wait(&rw_mutex);

    count++;
    printf("Writer%d upcounting .... Count : %d\n",id, count);



    sem_post(&rw_mutex);

    sleep(1);

  }
}
