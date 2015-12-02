
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
        printf("philosopher 0 먹는중.\n");
        sleep(10);
        down(0);
        printf("philosopher 0 생각중. \n");
        sleep(10);
        
    }while(1);
}
void *philosopher1(void *data)
{
    
    do{
        up(1);
        
        printf("philosopher 1 먹는중.\n");
        sleep(10);
        down(1);
        printf("philosopher 1 생각중. \n");
        sleep(10);
        
    }while(1);
}
void *philosopher2(void *data)
{
    
    do{
        up(2);
        
        printf("philosopher 2 먹는중.\n");
        sleep(10);
        down(2);
        printf("philosopher 2 생각중. \n");
        sleep(10);
        
        
    }while(1);
}
void *philosopher3(void *data)
{
    
    do{
        up(3);
        
        printf("philosopher 3 먹는중.\n");
        sleep(10);
        down(3);
        printf("philosopher 3 생각중. \n");
        sleep(10);
        
    }while(1);
}
void *philosopher4(void *data)
{
    
    do{
        up(4);
        
        printf("philosopher 4 먹는중.\n");
        sleep(10);
        down(4);
        printf("philosopher 4 생각중. \n");
        sleep(10);
        
    }while(1);
}

void up(int me)
{
    time_t t;
    int temp;
    int gap=0;
    int c=0;
    my_lock(chopstick[me]);
    printf("%d가 왼쪽 젓가락을 잡음.\n",me); //왼쪽 젓가락을 각각 확보하게 만듦
    
    
    ///////////////////////////////
    
    
    
    t = time(NULL);
    temp =(int) t;
    
    sleep(10); //슬립함수를 이용해서 계속 잡고 있게 만듦 써큘러 웨이트 형성.
    
    t = time(NULL);
    t = (int) t;
    
    gap = t-temp; //얼마나 지났는지 측정하기 위해서 time함수를 이용하였다. 아까 시간과 지금 시간을 빼서 얼마나 지났는지 구했다.
    //printf("gap %d\n",gap);
    
    c = 0;
    if(gap >=10)//만약 10초이상 지났으면 4번째 철학자가 왼쪽 젓가락을 놓게 한다.
    {
        if(me > (me+1)%5) //모두다 왼쪽 젓가락 (작은젓가락) 잡고있는데 오른젓가락이 작은철학자(여기서 4번째 철학자)는 오른쪽젓가락 잡게 함
        {
            my_unlock(chopstick[me]);//마지막 철학자가 왼쪽 젓가락을 놓게 된다.
            my_lock(chopstick[(me+1)%5]); //오른쪽 젓가락을 잡게 된다.
            printf("%d가 왼쪽을 놓고 오른쪽을 잡음\n",me);
            
            my_lock(chopstick[me]); //왼쪽을 잡으려고 한다
            printf("%d가 왼쪽도 마저 잡음\n"); //만약잡으면 밥을 먹을 수 있을 것이다.
            c=1;
        }//이 조건문을지나게되면 c가 1이 된다.
        
    }
    /////////////////////////////////10초 이상 지나지 않았으면(데드락이 걸리지 않았으면)
    //위의 조건문을지나지 않게 되어 c는 여전히 0이 된다.
    if(c == 0)//마지막철학자가 왼쪽젓가락을 놓게 되어 철학자들은 오른쪽젓가락을 잡을 수 있게 되어 한명 씩 밥을 먹기 시작할 것이다.
    {
        
        my_lock(chopstick[(me+1)%5]);
        printf("%d가 오른쪽 젓가락을 잡음.\n",me);
    }
    
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
