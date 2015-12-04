#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


int count=0;



/*


this function is runned by phreads
*/
void* count_plus(void *data)
{

    pthread_t self;
    self = pthread_self();
    int tmp;
    void * tmp2;


    printf("Thread id %8u is Created. \n",self);

    while(count <1000)
    {


        sleep(1);
        tmp = count;
        tmp = tmp+1;
        count = tmp;

        printf("Thread id :%8u count : %d . \n",self,count);


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
    printf("system down");

    return 0;
}
