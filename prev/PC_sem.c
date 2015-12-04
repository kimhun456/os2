#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
// buufer size is 10 
#define BUFFER_SIZE 10



int buffer[BUFFER_SIZE];
int counter=0;
int in=0;
int out=0;


// declare the semaphore
sem_t mutex;
sem_t empty;
sem_t full;




void *producer(void *data)
{
	int produce = 0;
	int i=0;

	while(1)
	{
		sem_wait(&empty);
		sem_wait(&mutex);
		
		//produce the item 
		buffer[in] = produce;
		printf("< Producer > counter : %d  buffer[%d] : %d\n",counter, in, produce);
		in = (in+1)%BUFFER_SIZE;
		produce++;

		sleep(1);
		counter++;
		sem_post(&mutex);
		sem_post(&full);
	}
}



void *consumer(void *data)
{
	int consume;
	int i;
	while(1)
	{
		sem_wait(&full);
		sem_wait(&mutex);
		//consume the item	
		consume=buffer[out];
		printf("<Consumer> counter : %d  buffer[%d] : %d\n",counter, out, consume);
		out = (out +1) % BUFFER_SIZE;
		
		sleep(1);
		counter --;
		sem_post(&mutex);
		sem_post(&empty);
	}
}



int main(){

	
	int i=0;
	pthread_t pthread[4];

	
	sem_init(&empty,0,10); 
	sem_init(&full,0,0); 
	sem_init(&mutex,0,1);

	
	// producer 2 , consumer 2 is created
	pthread_create(&pthread[0],NULL,producer,NULL);
	pthread_create(&pthread[1],NULL,consumer,NULL);
	pthread_create(&pthread[2],NULL,producer,NULL);
	pthread_create(&pthread[3],NULL,consumer,NULL);
	

	while(i<4){

	pthread_join(pthread[i],NULL);
	i++;
	}



	return 0;
}
