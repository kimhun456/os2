#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BOOKPAGES 10000
#define READ_THREADS 2
#define WRITE_THREADS 1

sem_t read_mutex;
sem_t write_mutex;


int readCount=0;
int count = 0;
int books[BOOKPAGES];

int currentPage = 0;

void * Writer(void *arg)
{
    int id = (int)arg;
    while(1){
      sleep(1);

      printf("Writer %d is try to enter\n",id);
      sem_wait(&write_mutex);

      books[currentPage++] = count++;

      printf( "Writer %d is writting  %d  \n",id,count);


      sem_post(&write_mutex);

      printf("Writer %d is leaving \n",id);
    }

}



void *Reader(void *arg)
{


    int id=(int)arg;
    int i;

    while(1){
        sleep(1);

        printf("Reader %d is try to enter\n",id);

        sem_wait(&read_mutex);
        readCount++;
        if(readCount==1)
        {
            sem_wait(&write_mutex);


            printf("Reader %d is reading\n",id);
        }
        sem_post(&read_mutex);


        // read하는 부분!!!!
        printf(" Reader %d's read data : ",id);
        for(i=0;i<count;i++){
          printf("%3d" ,books[i]);
        }
        printf("\n");

        sem_wait(&read_mutex);

        readCount--;
        if(readCount==0)
        {
            printf("Reader %d is leaving",id);
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

    // int a = 1;
    // int b = 2;
    //
    // pthread_create(&Reader_threads[0],NULL,Reader,(void *)a);
    // pthread_create(&Reader_threads[1],NULL,Reader,(void *)b);
    // pthread_create(&Writer_threads[0],NULL,Writer,(void *)a);
    //
    // pthread_join(Reader_threads[0],NULL);
    // pthread_join(Reader_threads[1],NULL);
    // pthread_join(Reader_threads[0],NULL);


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
