#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>


/*
	젓가락을 잡았다는 것을 표현하기만 하는 chopstick배열을 가지고
	표현하였다. 하지만 이 것만 가지고는 동기화를 맞출수 없다.
*/
int chopstick[5] = {0,0,0,0,0};


/*
	젓가락을 잡는 것을 표현한 함수이다.
	먼저 왼쪽에 있는 젓가락을 잡게되고
	그 이후 오른쪽에 있는 젓가락을 잡게 된다.
*/
void pick_chopstick(int id)
{
	//왼쪽에 있는 젓가락을 잡는다.
	chopstick[id] = 1;
	printf("philosopher %d is pick up the left chopstick %d .\n",id,id);

	sleep(1);
	//오른쪽에 있는 젓가락을 잡는다.
	chopstick[(id+1)%5] = 1;
	printf("philosopher %d is pick up the right chopstick %d .\n",id,(id+1)%5);

}


/*
	젓가락을 놓는 것을 표현한 함수이다.
	먼저 왼쪽에 있는 젓가락을 놓게 되고
	그 이후 오른쪽에 있는 젓가락을 놓게 된다.
*/
void take_down_chopstick(int id)
{

	chopstick[id] = 0; //내려놓는 것을 0으로 표현했다.
	printf("philosopher %d is take down the left chopstick %d .\n",id,id);
	sleep(1);
	chopstick[(id+1)%5] = 0;
	printf("philosopher %d is take down the right chopstick %d .\n",id,(id+1)%5);
}



/*
	철학자의 행동을 나타내는 함수이다.

*/
void *philosopher(void* data)
{

		int id = (int)data;

		while(1){

			sleep(1);

			printf("philosopher %d is hungry.\n",id);

			// 철학자가 배고파지면 젓가락 집기를 시도한다.
			pick_chopstick(id);
			// 젓가락을 모두 가지고 있다면 먹기시작한다.
			if(chopstick[id] == 1 && chopstick[(id+1)%5] ==1)
			{
				printf("philosopher %d is eating.\n",id);
				sleep(1);
				// 다먹고 난 뒤에 젓가락을 내려 놓는다.
				take_down_chopstick(id);
				printf("philosopher %d is thinking.\n",id);
				sleep(1);
			}
		}
}

int main(){

	int i=0;

	// 철학자가 될 쓰레드이다.
	pthread_t pthred_philosopher[5];


	//스레드를 생성해준다.
	for(i=0;i<5;i++){
		pthread_create(&pthred_philosopher[i],NULL,philosopher,i);

	}
	//스레드를 기다려준다.
	for(i=0;i<5;i++){
		pthread_join(pthred_philosopher[i],NULL);
	}


	return 0;
}
