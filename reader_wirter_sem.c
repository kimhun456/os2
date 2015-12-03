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

      // write를 위환 세마포를 기다리게 된다.
      sem_wait(&write_mutex);

      // write 부분
      printf( "Writer %d is writting  %d  \n", id, count++ + 1);

      // write를 모두한 후에 세마포를 풀어준다.
      sem_post(&write_mutex);

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


        // readmutex를 받아 오게 된다.
        sem_wait(&read_mutex);

        // read를 하는 리더가 늘었으므로 1을 추가하게 된다.
        readCount++;

        // read하는 함수가 1일경우 write_mutex를 잠궈 주게 된다.
        if(readCount==1)
        {
            sem_wait(&write_mutex);

        }

        // read_mutex를 풀어주게 된다.
        sem_post(&read_mutex);


        // reader가 read하는 부분이다.
        printf(" Reader %d's read data : %d \n", id, count);


        //read mutex를 받고 풀어준다.
        sem_wait(&read_mutex);


        //Read가 끝났으므로 리더를 한개 줄인다.
        readCount--;


        //read를 하는 어떠한 reader가 없는경우 wirte_mutex를 풀어주게 되어 writer가 write 할 수 있게 된다.
        if(readCount==0)
        {
            sem_post(&write_mutex);
        }
        // read_mutex를 해제한다.
        sem_post(&read_mutex);

    }


}


int main()
{
    int i=0;


    // 세마포어를 초기화해준다.
    sem_init(&read_mutex,0,1);
    sem_init(&write_mutex,0,1);


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


    // 다쓴 semaphore를 정리한다.

    sem_destroy(&write_mutex);
    sem_destroy(&read_mutex);


    return 0;
}
