#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include<stdlib.h>
#define SIZE 5

sem_t mutex; 
sem_t empty;
sem_t full;

int in = -1;
int out = -1;
int number=6;
int buffer[SIZE];

void * producer(void * arg)
{
    while(number>=0)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
            int item=rand()%10;
            buffer[in]=item;

            printf("producer produced : %d",item);
            in=(in+1)%SIZE;

            int i=out;
            printf("\nBUFFER : ");
            while(i!=in)
            {
                printf("%d ",buffer[i]);
                i=(i+1)%SIZE;
            }
            printf("\n\n");
            number--;

        sem_post(&mutex);
        sem_post(&full);
    }
}
void * consumer(void * arg)
{
    while(number>=0)
    {
        sem_wait(&full);
        sem_wait(&mutex);
            int nextConsumed=buffer[out];
            out=(out+1)%SIZE;
            printf("consumer consumed : %d\n",nextConsumed);

            int i=out;
            printf("\nBUFFER : ");
            while(i!=in)
            {
                printf("%d ",buffer[i]);
                i=(i+1)%SIZE;
            }
            printf("\n\n");
            number--;
        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main() 
{ 
    sem_init(&mutex, 0, 1); 
    sem_init(&empty, 0, SIZE); //size=5
    sem_init(&full, 0, 0);

    pthread_t t1,t2; 
    pthread_create(&t1,NULL,producer,NULL); 
    pthread_create(&t2,NULL,consumer,NULL); 

    pthread_join(t1,NULL); 
    pthread_join(t2,NULL); 

    sem_destroy(&mutex); 
    sem_destroy(&full); 
    sem_destroy(&empty); 
    return 0; 
} 






