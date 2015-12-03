#define N 5 /* number of philos */
#define LEFT (i+N-1)%N /* # of i's left */
#define RIGHT (i+1)%N /* # of i's right */
#define THINKING 0
#define HUNGRY 1
#define EATING 2
int state[N]; /* keep track of state */ semaphore mutex = 1;
semaphore s[N]; /* semaphore per philo */

void philosopher(int i) {
  while (TRUE) {
    think(); /* thinking */
    take_forks(i); /* get two forks, block */
    eat(); /* eating */
    put_forks(i); /* give up forks */
  }
}

void take_forks(int i) {
  wait(mutex);
  state[i] = HUNGRY;
  test(i); /* try getting 2 forks */
  signal(mutex);
  wait(s[i]); /* block if no forks acquired */
}
void test(int i) {
  if ( state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING ) {
    signal(s[i]);
  }
}

void put_forks(int i) {
  wait(mutex);
  state[i] = THINKING;
  test(LEFT);
  test(RIGHT);
  signal(mutex);
}
