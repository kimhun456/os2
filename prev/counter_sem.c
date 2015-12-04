#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int count=0;

void* count_plus(void *data)
{

    pthread_t self;
    self = pthread_self();
    int tmp;
    void * tmp2;


    printf("Thread id %8u is Created. \n",self);

    while(count <1000)
    {
       	pthread_mutex_lock(&mutex);

        sleep(1);
        tmp = count;
        tmp = tmp+1;
        count = tmp;

        printf("Thread id :%8u count : %d . \n",self,count);
       	pthread_mutex_unlock(&mutex);

    }
    return tmp2;
}


int main(){

    int i=0;

    pthread_t pthread[3];

    for(i=0; i<3; i++){

        pthread_create(&pthread[i], NULL ,count_plus ,NULL);

    }

    for(i=0;i<3;i++){
        pthread_join(pthread[i],NULL);
    }


   	pthread_mutex_destroy(&mutex);
    printf("system down");

    return 0;
}
