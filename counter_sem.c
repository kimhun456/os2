#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

int count=0;
sem_t sem;

void *count_plus(void *data)
{
	pthread_t id;
	int tmp;
	id = pthread_self();
	int i=0;

	printf("Thread %lu is Created. \n",id);

	while(1)
	{
		sem_wait(&sem);
		sleep(1);
		tmp = count;
		tmp = tmp+1;
		count = tmp;

		printf("Thread %lu count : %d . \n",id,count);
		sem_post(&sem);
		usleep(1);
	}
}


int main(){

	int i=0;

	pthread_t pthread[3];

	if(sem_init(&sem,0,1) == -1 ){
		perror("error occurs");
		exit(0);
	}

	for(i=0; i<3; i++){
		pthread_create(&pthread[i],NULL,count_plus,NULL);

	}
	pthread_join(pthread[0],NULL);
	pthread_join(pthread[1],NULL);
	pthread_join(pthread[2],NULL);

	return 0;
}
