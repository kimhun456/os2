#include <stdio.h>
#include <pthread.h>
// buufer size is 10
#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int counter=0;
int in=0;
int out=0;

void *producer(void *data)
{
	int produce = 0;
	int i=0;

	while(1)
	{

		buffer[in] = produce;

		printf("< Producer > counter : %d  buffer[%d] : %d\n",counter+1, in, produce);

		in = (in+1)%BUFFER_SIZE;
		produce++;
		sleep(1);
		counter++;

	}
}

void *consumer(void *data)
{
	int consume;
	int i;
	while(1)
	{

		consume=buffer[out];
		printf("< Consumer > counter : %d  buffer[%d] : %d\n",counter-1, out, consume);
		out = (out +1) % BUFFER_SIZE;
		sleep(1);
		counter --;

	}
}



int main(){

	int i=0;

	pthread_t pthread[4];

	pthread_create(&pthread[0],NULL,producer,NULL);
	pthread_create(&pthread[1],NULL,consumer,NULL);
	pthread_create(&pthread[2],NULL,producer,NULL);
	pthread_create(&pthread[3],NULL,consumer,NULL);

	while(i<4)
	{
		pthread_join(pthread[i],NULL);
		i++;
	}
	return 0;
}
