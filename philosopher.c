#include <stdio.h>
#include <pthread.h>

#define THINK 0
#define HUNGRY 1
#define EAT 2


int food = 5;
int state[5];

void *count_plus(void *data)
{
	pthread_t id;
	int tmp;
	id = pthread_self();
	int i=0;

	printf("Thread %lu is Created. \n",id);

	while(1)
	{
		
		sleep(1);
		tmp = count;
		tmp = tmp+1;
		count = tmp;

		printf("Thread %lu count : %d . \n",id,count);

	}
}

void *count_plus(void *data)
{
	pthread_t id;
	int tmp;
	id = pthread_self();
	int i=0;

	printf("Thread %lu is Created. \n",id);

	while(1)
	{
		
		sleep(1);
		tmp = count;
		tmp = tmp+1;
		count = tmp;

		printf("Thread %lu count : %d . \n",id,count);

	}
}


int main(){

	int i=0;
	
	pthread_t phliosophers_thread[5];

	for(i=0; i<5; i++){
		pthread_create(&phliosophers_thread[i],NULL,count_plus,NULL);
		
	}
	for(i =0; i<5; i++){
		pthread_join(phliosophers_thread[i],NULL);
	}
	return 0;
}
