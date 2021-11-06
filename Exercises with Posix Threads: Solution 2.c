\* 
compile with:
	g++ threadex2.cpp -lpthread -o thread2
   
run with:
	.\thread2
*\

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

void *functionC(void *);

// initialize mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int  counter = 0;
int temp;

int main()
{
   	int rc1, rc2;
   
 //declare the ids of thread 1 and thread 2
	pthread_t thread1, thread2;

 // Create two independent threads each of which will execute functionC 

   if( (rc1=pthread_create( &thread1, NULL, &functionC, NULL)) )
   {
      printf("Thread creation failed: %d\n", rc1);
   }
   if( (rc2=pthread_create( &thread2, NULL, &functionC, NULL)) )
   {
      printf("Thread creation failed: %d\n", rc2);
   }

// Wait till threads are completed before main continues (notice however that threads do never return).   
 
   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL);
   exit(0);
}
 
void *functionC(void *)
{
	while(1)
	{
 	// lock mutex (try to see how the behaviour changes if the mutex is present or absent)
   	pthread_mutex_lock( &mutex1 );

   	temp = counter; 
   	temp = temp + 1;
   	
	// introduce a delay of one second to increase the probability of a preemption to occur
	sleep(1);
   	counter=temp;

	// print counter value
   	printf("Counter value: %d\n",counter);
	
	// unlock mutex (try to see how the behaviour changes if the mutex is present or absent)
	pthread_mutex_unlock( &mutex1 );
	}
}

// OPTIONAL: try to define the mutex as a "recursive" (see the slides about the concept of a "recursive mutex"). Each
// thread must call the lock function and the unlock function twice to test the mechanism.

