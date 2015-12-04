#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>


#define N 5 /* number of philos */
#define LEFT (i+N-1)%N /* # of i's left */
#define RIGHT (i+1)%N /* # of i's right */
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N]; /* keep track of state */

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t s[N] = PTHREAD_MUTEX_INITIALIZER;
//sem_t s[N]; /* semaphore per philo */

void put_forks(int);
void* philosopher(int*);
void take_forks(int);
void test(int);

void think(int i){
  printf("philosopher %d is thinking\n",i);
    sleep(1);
}
void eat(int i){
  printf("philosopher %d is eating\n",i);
    sleep(1);
}


void* philosopher(int *data) {

  int i = (int)data;

  while (1) {
    think(i); /* thinking */
    take_forks(i); /* get two forks, block */
    eat(i); /* eating */
    put_forks(i); /* give up forks */
  }
}

void take_forks(int i) {

  printf("philosopher %d want to eat!!\n",i);
  pthread_mutex_lock(&mutex);
  state[i] = HUNGRY;


  test(i); /* try getting 2 forks */

  pthread_mutex_unlock(&mutex);
  pthread_mutex_lock(&s[i]); /* block if no forks acquired */


  printf("philosopher %d take the forks... LEFT : %d RIGHT : %d \n", i, LEFT, RIGHT);

}

void test(int i) {
  if ( state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING ) {
    pthread_mutex_unlock(&s[i]);
  }
}

void put_forks(int i) {
  pthread_mutex_lock(&mutex);
  state[i] = THINKING;

  test(LEFT);
  test(RIGHT);
  pthread_mutex_unlock(&mutex);

  printf("philosopher %d put the forks... LEFT : %d RIGHT : %d \n", i, LEFT, RIGHT);
}

int main(){
  int i,j;

  pthread_t pthread[N];

  for (i = 0; i < N; i++) {
    state[i] = THINKING;
  }

  for (j = 0; j < N; j++) {
    pthread_create(&pthread[j], NULL, philosopher, (void *)j);
  }

  for (j = 0; j < N; j++)
    pthread_join(pthread[j],NULL);

  return 0;

}
