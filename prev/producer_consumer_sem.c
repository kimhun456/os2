#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define BUFFERSIZE 100
#define CONSUMESIZE 100


/*
  생성한 아이템이 들어갈 버퍼를 등록한다.

*/
int buffer[BUFFERSIZE];
int in = -1;
int out = -1;
int count = 0;


/*
  동기화를 위해 뮤텍스와 뮤텍스 컨디션을 초기화시킨다.

*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t BUFFER_HAS_SPACE = PTHREAD_COND_INITIALIZER;
pthread_cond_t BUFFER_HAS_DATA = PTHREAD_COND_INITIALIZER;

/*
  producer스레드가 실행시키는 함수로서
  in 을 1증가시킨후 원형배열로 만들었기 때문에 검사한후에
  버퍼에 생산된 값을 넣어주게 된다.

*/
void *Producer(void* arg)
{
  int i;
    for(i=0;i<CONSUMESIZE;i++)
    {
      sleep(1);
      // 뮤텍스를 걸어 소비와 생산이 한번에 하나의 스레드만 들어갈 수 있게 해준다.
      pthread_mutex_lock(&mutex);

      if(count==BUFFERSIZE)
      {   // 만약 버퍼가 꽉차게 된다면 생산자가 소비할 때까지 기다린다.
          pthread_cond_wait(&BUFFER_HAS_SPACE,&mutex);
      }

      in++;
      in%=BUFFERSIZE;
      buffer[in]=i;
      count++;
      printf("Produce : %d \n",i);


      // 생산이 끝나면 버퍼가 데이터가 있다는것을 알려준다.
      pthread_cond_signal(&BUFFER_HAS_DATA);


      // 뮤텍스를 해제한다.
      pthread_mutex_unlock(&mutex);

    }

}


/*
  Consumer 스레드가 실행시키는 함수로서 소비해야되는 out을 1증가시키고
  마찬가지로 원형 배열이기 때문에 버퍼사이즈로 나눠준 후에
  buffer[out]에 있는 소비해야될 재화를 출력하게 된다.

*/
void *Consumer(void* arg)
{
  int data;
  int i;
  for(i=0;i<CONSUMESIZE;i++)
  {


    sleep(1);

    // 한번에 하나의 스레드만 들어갈 수 있게 뮤텍스락을 걸어준다.
    pthread_mutex_lock(&mutex);
    if(count==0)
    {
        // 만약 버퍼에 아무것도 존재하지 않다면 데이터가 들어 올때까지 기다리게 된다.
        pthread_cond_wait(&BUFFER_HAS_DATA,&mutex);
    }

    out++;
    out %=BUFFERSIZE;
    data = buffer[out];
    count --;

    printf("Consume : %d\n",data);


    // 이제 생산할 공간이 있다는 것을 알려준다.
    pthread_cond_signal(&BUFFER_HAS_SPACE);


    // 뮤텍스를 풀게 된다.
    pthread_mutex_unlock(&mutex);


  }
}


int main()
{

    int i;


    // 버퍼를 -1 로 채워서 consumer가 제대로 소비를 하는지 추적한다.
    for(i=0;i<BUFFERSIZE;i++){
      buffer[i]= -1;
    }


    // 스레드 2개를 생성하여  각각 컨슈머와 프로듀서에게 할당한다.
    pthread_t threads[2];

    pthread_create(&threads[0],NULL,Producer,NULL);
    pthread_create(&threads[1],NULL,Consumer,NULL);


    // 스레드가 끝내길 기다린다.
    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);

    // 뮤텍스 컨디션을 해제한다.
    pthread_cond_destroy(&BUFFER_HAS_SPACE);
    pthread_cond_destroy(&BUFFER_HAS_DATA);


    // 모든 스레드를 해제한다.
    pthread_exit(NULL);

    return 0;
}
