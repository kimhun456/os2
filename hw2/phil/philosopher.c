/**
 * General structure of a dining philosopher
 *
 * Alternate between thinking/eating
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include "dp.h"

void *philosopher(void *param)
{
	int *lnumber = (int *)param;
	int number = *lnumber;
	int sleep_time;
	int times_through_loop = 0;

	srandom((unsigned)time(NULL));

	while (times_through_loop < 5) {

		/* THINKING PHASE */
		sleep_time = (int)((random() % MAX_SLEEP_TIME) + 1);
		thinking(sleep_time);

		/* try to eat */
		pickup_forks(number);
		printf("Philosopher %d is eating\n",number);

		/* once succeed to picup the forks */
		sleep_time = (int)((random() % MAX_SLEEP_TIME) + 1);
		/* eat */
		eating(sleep_time);

		/* then go back to think */
		printf("Philosopher %d is thinking\n",number);
		return_forks(number);
		
		/* end of one iteration */
		++times_through_loop;
	}
}
