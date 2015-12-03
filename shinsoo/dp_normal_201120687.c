#include <stdio.h>
#include <pthread.h>


#define THREAD_NUM 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (data+THREAD_NUM-1)%THREAD_NUM
#define RIGHT (data+1)%THREAD_NUM


int state[THREAD_NUM];


void *philosopher(void *data);
void take(int data);
void test(int data);
void put(int data);


int main(){

  int i,j;
  pthread_t pthread[THREAD_NUM];

  for(i=0; i<THREAD_NUM; i++){
    pthread_create(&pthread[i], NULL, philosopher, (void*)i);
  }

  for(i=0; i<THREAD_NUM; i++){
    pthread_join(pthread[i], NULL);
  }

  return 0;
}



void *philosopher(void *data){

  int id = (int)data;

  printf("Philosopher%d is thinking......\n",id);

  while(1){

    sleep(1);
    take(id);

    sleep(0);
    put(id);

  }

}

void take(int data){

  int id = data;

  state[id] = HUNGRY;
  printf("Philosopher%d is Hungry :(\n",id);
  test(id);

  sleep(1);

}


void test(int data){

  int id = data;

  if(state[id] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING){
    state[id] = EATING;
    sleep(1);
    printf("\nPhilosopher%d takes fork...\n",id);
    printf("Philosopher%d is Eating !!!!\n\n",id);
  }
}



void put(int data){
  int id = data;

  state[id] = THINKING;
  printf("Philosopher%d put fork down.\n",id);
  printf("Philosopher%d is thinking......\n",id);

  test(LEFT);
  test(RIGHT);
}
