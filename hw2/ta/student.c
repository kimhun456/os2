/**
 * General structure of a student.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"

void *student_loop(void *param)
{
	int *lnumber = (int *)param;
	int number = *lnumber;
	int sleep_time;
	int times_through_loop = 0;

	srandom((unsigned)time(NULL));

	while (times_through_loop < 5) {

		/* first, a student tries to do the homework by her/himself */
		sleep_time = (int)((random() % MAX_SLEEP_TIME) + 1);
		hang_out(*lnumber,sleep_time);

		/***************************************
		* FILL IN YOUR CODE HERE 
		***************************************/

		/* Once they realize they need help, 
		acquire the mutex lock to check the status of the waiting students */

		
		/* if there is a seat for me */
		if (waiting_students < NUM_OF_SEATS) {
			/* adjust the number of students */
			++waiting_students;
			printf("\t\tStudent %d takes a seat waiting = %d\n",*lnumber, waiting_students);

			/* signal the TA for the existence of a waiting student, i.e., wake the TA up */

			/* release the mutex lock */

			/* waits for the T.A. in case he/she is helping another student */
			
			printf("Student %d receiving help\n",*lnumber);
			

			/* end of one iteration */
			++times_through_loop;
		} else {
			/* if no seat is available */
			printf("\t\t\tStudent %d will try later\n",*lnumber);
			pthread_mutex_unlock(&mutex_lock);
		}
	}
}

