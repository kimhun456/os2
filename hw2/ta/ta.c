/**
 * General structure of the teaching assistant.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"

void *ta_loop(void *param)
{
	int sleep_time;

	/* seed random generator */
	srandom((unsigned)time(NULL));

	while (1) {

		/*************************************
		* FILL IN YOUR CODE HERE
		************************************/

		/* if no student shows up, wait (taking a nap) */
		while(waiting_students==0);

		/* if there is a student, acquire the mutex lock */
		
		/* adjust the number of waiting students */
		--waiting_students;
		printf("currently waiting student is %d\n",waiting_students);

		/* indicate the TA is ready to help a student */

		/* release the acquired mutex lock */


		/* help the student */	
		sleep_time = (int)((random() % MAX_SLEEP_TIME) + 1);
		help_student(sleep_time);
	}
}

