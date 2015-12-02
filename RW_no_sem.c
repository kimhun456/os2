#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>


#define BUFFER 10

char string[10];

void *reader(void *data)
{
	char read[10];
	while(1){
		
		strcpy(read,string);
		sleep(1);
		printf("< reader > : %s\n",read);


	}
}






void *writer1(void *data)
{

	while(1)
	{

		strcpy(string," Kim ");
		sleep(1);
		printf("< writer > : %s\n",string);

	}

}

void *writer2(void *data)
{

	while(1)
	{

		strcpy(string," Hyun ");
		sleep(1);
		printf("< writer > : %s\n",string);

	}

}


int main(){

	int i=0;

	pthread_t pthread[4];

	pthread_create(&pthread[0],NULL,writer1,NULL);
	pthread_create(&pthread[1],NULL,reader,NULL);
	pthread_create(&pthread[2],NULL,writer2,NULL);
	pthread_create(&pthread[3],NULL,reader,NULL);

	while(i<4)
	{
		pthread_join(pthread[i],NULL);
		i++;
	}
	return 0;
}
