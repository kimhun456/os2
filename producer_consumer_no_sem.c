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

      in++;
      in%=BUFFERSIZE;
      buffer[in]=i;

      printf("Produce : %d \n",i);

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

    out++;
    out %=BUFFERSIZE;
    data = buffer[out];


    printf("Consume : %d\n",data);
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


    // 모든 스레드를 해제한다.
    pthread_exit(NULL);

    return 0;
}
