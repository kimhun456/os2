/**
 * Header file for dining philosophers
 */

#include <pthread.h>

// the number of philosophers
#define NUMBER 		5

// the maximum time (in seconds) to sleep
#define MAX_SLEEP_TIME	5

// different philosopher states
//#define THINKING		0
//#define HUNGRY			1
//#define EATING			2

// the state of each philosopher (THINKING, HUNGRY, EATING)
//int state[NUMBER];
enum phil_status {THINKING, HUNGRY, EATING};
extern enum phil_status state[NUMBER];

// condition variables and associated mutex lock
extern pthread_cond_t		cond_vars[NUMBER];
extern pthread_mutex_t 	mutex_lock;

void *philosopher(void *param);
