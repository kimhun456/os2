///////////////�������� �̿��ߴµ� ������ȿ� �ִ� ���̴� �ʷμ���///////////////////
#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
//#include <semaphore.h>
//sem_t chopstick[5];

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#define BUFFER_SIZE 10

int chopstick[5] = {0,0,0,0,0};

int buffer[BUFFER_SIZE];
int counter=0;
int in=0;
int out=0;
int mutex=1;
int empty=10;
int full=0;

union semun
{
   int val;
   struct semid_ds *buf;
   ushort *array;
};

struct sembuf lock_op = {0,-1,SEM_UNDO};
struct sembuf unlock_op = {0,1,SEM_UNDO};
int sem_id;

int sem_creat(void)
{
   int sem_id;
   union semun arg = {0};

   if((sem_id = semget(IPC_PRIVATE,1,0600 | IPC_CREAT | IPC_EXCL)) <0)
   {
      perror("segment()-error");
      exit(1);
   }
   arg.val=1;
   if(semctl(sem_id,0,SETVAL, arg)<0)
   {
      perror("semctl()-SETVAL error");
      exit(1);
   }
   return sem_id;
}

void my_lock(int sem_id)
{
	semop(sem_id, &lock_op, 0);
   //if(semop(sem_id, &lock_op, 0)<0)
//   {
   //   perror("semop()-lock error");
    //  exit(1);
   //}
}

void my_unlock(int sem_id)
{
semop(sem_id, &unlock_op, 1);
   //if(semop(sem_id, &unlock_op, 1)<0)
  // {
  //    perror("semop()-lock error");
    //  exit(1);
   //}
}


void *philosopher0(void *data)
{

	do{
		up(0);
		printf("philosopher 0 �Դ���.\n");
		sleep(10);
		down(0);
		printf("philosopher 0 ������. \n");
		sleep(10);

	}while(1);
}
void *philosopher1(void *data)
{

	do{
		up(1);

		printf("philosopher 1 �Դ���.\n");
		sleep(10);
		down(1);
		printf("philosopher 1 ������. \n");
		sleep(10);

	}while(1);
}
void *philosopher2(void *data)
{

	do{
		up(2);

		printf("philosopher 2 �Դ���.\n");
		sleep(10);
		down(2);
		printf("philosopher 2 ������. \n");
		sleep(10);


	}while(1);
}
void *philosopher3(void *data)
{

	do{
		up(3);

		printf("philosopher 3 �Դ���.\n");
		sleep(10);
		down(3);
		printf("philosopher 3 ������. \n");
		sleep(10);

	}while(1);
}
void *philosopher4(void *data)
{

	do{
		up(4);

		printf("philosopher 4 �Դ���.\n");
		sleep(10);
		down(4);
		printf("philosopher 4 ������. \n");
		sleep(10);

	}while(1);
}

void up(int me)
{

	my_lock(chopstick[me]);
	printf("%d�� ���� �������� ����.\n",me);

	sleep(10);	//���⿡ �Ϻη� �����Լ��� �̿��Ͽ� ��� ö���ڵ��� ���� �������� Ȯ���ϰ� �������������� ��ٸ��� �������.

	my_lock(chopstick[(me+1)%5]);
	printf("%d�� ������ �������� ����.\n",me);


}

void down(int me)
{
	my_unlock(chopstick[me]);
	my_unlock(chopstick[(me+1)%5]);

}


int main(){

	int i=0;

	for(i=0;i<5;i++)
	{
		chopstick[i] = sem_creat();
	}

	i=0;

	pthread_t pthread[4];

	pthread_create(&pthread[0],NULL,philosopher0,NULL);
	pthread_create(&pthread[1],NULL,philosopher1,NULL);
	pthread_create(&pthread[2],NULL,philosopher2,NULL);
	pthread_create(&pthread[3],NULL,philosopher3,NULL);
	pthread_create(&pthread[4],NULL,philosopher4,NULL);


	i =0;
	while(i<5)
	{
		pthread_join(pthread[i],NULL);
		i++;
	}
	return 0;
}
