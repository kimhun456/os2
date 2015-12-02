#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>


//#define BUFFER_SIZE 10

int readcount=0;
sem_t mutex ;
sem_t wrt;
char string[10];

void *reader(void *data)
{
	char read[10];
	while(1){
		sem_wait(&mutex);
		if(readcount ==1) {
			wait(wrt);}
		
		sem_post(&mutex);
		strcpy(read,string);	
		printf("< reader > : %s\n",read);	
		
		sem_wait(&mutex);
		readcount--;
		if(readcount ==0) 
			sem_post(&wrt); 
		sem_post(&mutex);	
			
		sleep(1);	
	}
}


void *writer1(void *data)
{
	while(1)
	{		
		sem_wait(&wrt);
		strcpy(string," Kim ");	
		printf("< writer 1 > : %s\n",string);
		sem_post(&wrt);
		sleep(1);	
		
	}

}

void *writer2(void *data)
{
	while(1)
	{		
		sem_wait(&wrt);
		strcpy(string," Hyun ");	
		printf("< writer 2 > : %s\n",string);
		sem_post(&wrt);
		sleep(1);
	}

}






int main(){

	int i=0;

	// semaphore is intialized 
	sem_init(&mutex,0,1);
	sem_init(&wrt,0,1);

	pthread_t pthread[4];
	
	pthread_create(&pthread[0],NULL,writer1,NULL);
	pthread_create(&pthread[1],NULL,writer2,NULL);
	pthread_create(&pthread[2],NULL,reader,NULL);
	pthread_create(&pthread[3],NULL,reader,NULL);

	while(i<4)
	{
		pthread_join(pthread[i],NULL);
		i++;
	}

	return 0;
}
