/**
 * Header file for dining philosophers
 */

#include <pthread.h>
#include <semaphore.h>

/* the maximum time (in seconds) to sleep */
#define MAX_SLEEP_TIME	5

/* number of maximum waiting students */
#define MAX_WAITING_STUDENTS	3

/* number of potential students */
#define NUM_OF_STUDENTS	10	

/* number of available seats */
#define NUM_OF_SEATS	3

/* semaphores and mutex lock */
extern pthread_mutex_t 	mutex_lock;

/* semaphore declarations */
extern sem_t			students_sem;
extern sem_t			ta_sem;

/* the number of waiting students */
extern int waiting_students;

/* student being served */
extern int student_number;

/* the numeric id of each student */
extern int student_id[NUM_OF_STUDENTS];

/* student function prototype */
void *student_loop(void *param);

/* ta function prototype */
void *ta_loop(void *param);

