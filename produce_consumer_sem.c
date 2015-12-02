# include <stdio.h>
# include <pthread.h>
#include <stdlib.h>
# define BufferSize 100
# define CONSUMESIZE 200

int buffer[BufferSize];
int count = 0 ;
int in = -1;
int out = -1;


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t BUFFER_HAS_SPACE = PTHREAD_COND_INITIALIZER;
pthread_cond_t BUFFER_HAS_DATA = PTHREAD_COND_INITIALIZER;

void *Producer(void* arg)
{
  int i;
    for(i=0;i<CONSUMESIZE;i++)
    {

      printf(" producer data = %d\n",i);

      pthread_mutex_lock(&mutex);
      if(count==BufferSize)
      {
          pthread_cond_wait(&BUFFER_HAS_SPACE,&mutex);
      }

      in++;
      in%=BufferSize;
      buffer[in]=i;
      count++;

      printf("Produce : %d \n",i);

      pthread_cond_signal(&BUFFER_HAS_DATA);

      pthread_mutex_unlock(&mutex);


    }

}

void *Consumer(void* arg)
{

  int data;
  int i;
  for(i=0;i<CONSUMESIZE;i++)
  {



    pthread_mutex_lock(&mutex);
    if(count==0)
    {
        pthread_cond_wait(&BUFFER_HAS_DATA,&mutex);
    }

    out++;
    out %=BufferSize;
    data = buffer[out];
    count--;


    pthread_cond_signal(&BUFFER_HAS_SPACE);

    pthread_mutex_unlock(&mutex);

    printf("consumer data = %d\n",data);
  }
}


int main()
{


    pthread_t threads[2];

    pthread_create(&threads[0],NULL,Producer,NULL);
    pthread_create(&threads[1],NULL,Consumer,NULL);

    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);


    pthread_cond_destroy(&BUFFER_HAS_SPACE);
    pthread_cond_destroy(&BUFFER_HAS_DATA);

    pthread_exit(NULL);

    return 0;
}
