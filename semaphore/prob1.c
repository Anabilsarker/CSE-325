#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

int x=0;
sem_t syn;

void *my_func(void *arg)
{
  sem_wait(&syn);
  printf("x=%d \n",x);
  sem_post(&syn);

}

void main()
{
  pthread_t thread;

  if(sem_init(&syn, 0, 0) == -1){
     perror("Could not initialize mylock semaphore");
     exit(2);
  }

  if(pthread_create(&thread, NULL, my_func, NULL) < 0){
     perror("Error: thread cannot be created");
     exit(1);
   }

   sem_wait(&syn);
   x= 55;
   printf("x=%d \n",x);
   sem_post(&syn);
   pthread_join(thread, NULL);
   sem_destroy(&syn);
   exit(0);
}

