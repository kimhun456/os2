#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


/*
  변수들을 설정해준다.

*/
#define READ_THREADS 4
#define WRITE_THREADS 1



/*
  writer가 쓰게될 count를 정의한다.
  Reader 또한 count를 읽게 된다.
*/
int readCount=0;
int count = 0;



/*
  writer 쓰레드가 실행할 함수이다.
*/
void * Writer(void *arg)
{
    //id를 받아온다.
    int id = (int)arg;

    while(1){
      sleep(1);

      // write 부분
      printf( "Writer %d is writting  %d  \n", id, count++ + 1);

    }

}

/*
  Reader 쓰레드가 실행 할 함수이다.
*/
void *Reader(void *arg)
{

    //id를 받아온다.
    int id=(int)arg;

    while(1){
        sleep(1);



        printf(" Reader %d's read data : %d \n", id, count);



    }


}


int main()
{
    int i=0;


    // pthreads를 선언한다.
    pthread_t Reader_threads[100];
    pthread_t Writer_threads[100];


    // read_pthread를 생성한다.
    for(i=0;i<READ_THREADS;i++)
    {
        pthread_create(&Reader_threads[i],NULL,Reader,(void *)i);
    }

    // write Pthread를 생성한다.
    for(i=0;i<WRITE_THREADS;i++)
    {
        pthread_create(&Writer_threads[i],NULL,Writer,(void *)i);
    }


    /*
      pthread_join을 이용하여 쓰레드가 끝나기를 기다린다.
    */
    for(i=0;i<WRITE_THREADS;i++)
    {
        pthread_join(Writer_threads[i],NULL);
    }

    for(i=0;i<READ_THREADS;i++)
    {
        pthread_join(Reader_threads[i],NULL);
    }




    return 0;
}
