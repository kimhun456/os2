#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


/*
  변수들을 설정해준다.

*/
#define READ_THREADS 2
#define WRITE_THREADS 1


/*
  세마포어들을 설정한다.
  read_mutex는 read를 하기 위해서 필요하다.
  wirte_mutex는 writer가 쓰기 위해서 필요하다.

*/
sem_t read_mutex;
sem_t write_mutex;


int readCount=0;
int count = 0;


void * Writer(void *arg)
{
    int id = (int)arg;
    while(1){
      sleep(1);

      sem_wait(&write_mutex);


      printf( "Writer %d is writting  %d  \n", id, count++ +1);
      sem_post(&write_mutex);

    }

}



void *Reader(void *arg)
{


    int id=(int)arg;
    int i;

    while(1){
        sleep(1);

        sem_wait(&read_mutex);
        readCount++;
        if(readCount==1)
        {
            sem_wait(&write_mutex);


        }
        sem_post(&read_mutex);


        // read하는 부분!!!!
        printf(" Reader %d's read data : %d \n", id, count);

        sem_wait(&read_mutex);

        readCount--;


        if(readCount==0)
        {
            sem_post(&write_mutex);
        }
        sem_post(&read_mutex);

    }


}


int main()
{
    int i=0;

    sem_init(&read_mutex,0,1);
    sem_init(&write_mutex,0,1);

    pthread_t Reader_threads[100];
    pthread_t Writer_threads[100];

    for(i=0;i<READ_THREADS;i++)
    {
        pthread_create(&Reader_threads[i],NULL,Reader,(void *)i);
    }
    for(i=0;i<WRITE_THREADS;i++)
    {
        pthread_create(&Writer_threads[i],NULL,Writer,(void *)i);
    }

    for(i=0;i<WRITE_THREADS;i++)
    {
        pthread_join(Writer_threads[i],NULL);
    }

    for(i=0;i<READ_THREADS;i++)
    {
        pthread_join(Reader_threads[i],NULL);
    }

    sem_destroy(&write_mutex);
    sem_destroy(&read_mutex);

    return 0;
}
