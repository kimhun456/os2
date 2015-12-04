#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREAD_NUM 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (data+THREAD_NUM-1)%THREAD_NUM
#define RIGHT (data+1)%THREAD_NUM

#define MAX_SLEEP 5

// the state of each philosopher (THINKING, HUNGRY, EATING)
int state[THREAD_NUM];

// condition variables and associated mutex lock
pthread_cond_t		self[THREAD_NUM];	/* condition variables */
pthread_mutex_t 	mutex_lock;		/* for monitor implementation */

void *philosopher(void *data);
void take(int data);
void test(int data);
void put(int data);

int main(void)
{
  int i,j;
  pthread_t pthread[THREAD_NUM];

  for (i = 0; i < THREAD_NUM; i++) {
    state[i] = THINKING;
    pthread_cond_init(&self[i],NULL);
  }
  pthread_mutex_init(&mutex_lock, NULL);

  for (j = 0; j < THREAD_NUM; j++) {
		pthread_create(&pthread[j], NULL, philosopher, (void *)j);
	}

	for (j = 0; j < THREAD_NUM; j++)
		pthread_join(pthread[j],NULL);

	return 0;
}


void *philosopher(void *data)
{
	int id = (int)data;
	int sleep_time;
	//int times_through_loop = 0;

	srandom((unsigned)time(NULL));

	//do {
  while(1){
		/* THINKING PHASE */
		sleep_time = (int)((random() % MAX_SLEEP) + 1);
    printf("Philosopher%d is thinking......\n",id);
    sleep(sleep_time);

		/* try to eat */
		take(id);

		/* once succeed to picup the forks */
		sleep_time = (int)((random() % MAX_SLEEP) + 1);
		/* eat */
		sleep(sleep_time);

		/* then go back to think */
		//printf("Philosopher %d is thinking\n",id);
		put(id);

		/* end of one iteration */
		//++times_through_loop;
  }
	//}while (times_through_loop < THREAD_NUM);

}

void take(int data){

  int id = data;
  pthread_mutex_lock(&mutex_lock);

  state[id] = HUNGRY;
  printf("Philosopher%d is Hungry :(\n",id);

  test(id);
  if(state[id] != EATING) {
    pthread_cond_wait(&self[id],&mutex_lock);
  }
  pthread_mutex_unlock(&mutex_lock);

}


void test(int data){

  int id = data;

  if(state[id] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING){
    state[id] = EATING;
    printf("\nPhilosopher%d takes fork %d and %d...\n",id, id, RIGHT);
    printf("Philosopher%d is Eating !!!!\n\n",id);

    pthread_cond_signal(&self[id]);
    // pthread_mutex_unlock(&chopstick[id]);
    // pthread_mutex_unlock(&chopstick[(id+1)%THREAD_NUM]);
  }
}



void put(int data){
  int id = data;
  // pthread_mutex_unlock(&chopstick[id]);
  // pthread_mutex_unlock(&chopstick[(id+1)%THREAD_NUM]);
  //pthread_mutex_lock(&mutex_lock);
  state[id] = THINKING;
  printf("Philosopher%d put fork %d and %d down.\n",id, id, RIGHT);
  printf("Philosopher%d is thinking......\n",id);

  test(LEFT);
  test(RIGHT);
  //pthread_mutex_unlock(&mutex_lock);
  // pthread_mutex_unlock(&chopstick[id]);
  // pthread_mutex_unlock(&chopstick[(id+1)%THREAD_NUM]);
}
