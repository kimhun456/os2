#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

int chopstick[5] = {0,0,0,0,0};
int me =0;


void up(int me)
{
    
    //sem_wait(&chopstick[me]);
    if(chopstick[me]==0){
        chopstick[me] = 1;
        printf("%d가 왼쪽 젓가락을 잡음.\n",me);
    }else{
        printf("%d번째 젓가락이 사용중\n",me);
    }
    sleep(1);
    if(chopstick[(me+1)%5]==0){
        chopstick[(me+1)%5] = 1;
        printf("%d가 오른쪽 젓가락을 잡음.\n",me);
    }else{
        printf("%d번째 젓가락이 사용중\n",(me+1)%5);
    }
    
    
    
    
}

void down(int me)
{
    chopstick[me] = 0;
    sleep(1);
    chopstick[(me+1)%5] = 0;
}

void *philosopher0(void *data)
{
    int me = 0;
    
    do{
        up(me);//젓가락 잡기 시도
        if(chopstick[me] == 1 && chopstick[(me+1)%5] ==1) //왼쪽 오른쪽 양쪽 젓가락 다 잡고 있다면
        {
            printf("philosopher 0 먹는중.\n");
            sleep(1);
            down(me);//젓가락 내려놓기
            printf("philosopher 0 생각중. \n");
            sleep(1);
        }
        
    }while(1);
}
void *philosopher1(void *data)
{
    int me = 1;
    
    do{
        up(me);
        if(chopstick[me] == 1 && chopstick[(me+1)%5] ==1)
        {
            printf("philosopher 1 먹는중.\n");
            sleep(1);
            down(me);
            printf("philosopher 1 생각중. \n");
            sleep(1);
        }
        
    }while(1);
}
void *philosopher2(void *data)
{
    int me = 2;
    do{
        up(me);
        if(chopstick[me] == 1 && chopstick[(me+1)%5] ==1)
        {
            printf("philosopher 2 먹는중.\n");
            sleep(1);
            down(me);
            printf("philosopher 2 생각중. \n");
            sleep(1);
        }
        
    }while(1);
}
void *philosopher3(void *data)
{
    int me = 3;
    do{
        up(me);
        if(chopstick[me] == 1 && chopstick[(me+1)%5] ==1)
        {
            printf("philosopher 3 먹는중.\n");
            sleep(1);
            down(me);
            printf("philosopher 3 생각중. \n");
            sleep(1);
        }
        
    }while(1);
}
void *philosopher4(void *data)
{
    int me = 4;
    do{
        up(me);
        if(chopstick[me] == 1 && chopstick[(me+1)%5] ==1)
        {
            printf("philosopher 4 먹는중.\n");
            sleep(1);
            down(me);
            printf("philosopher 4 생각중. \n");
            sleep(1);
        }
    }while(1);
}




int main(){
    
    int i=0;
    
    
    
    
    pthread_t pthread[5];
    
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

