
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
 
void *print_message_function( void *ptr );

int result; 

int main()
{
     // Declare the ids of thread 1 and thread 2
     pthread_t thread1, thread2;
     const char *message1 = "1";
     const char *message2 = "2";
     int  iret1, iret2;
 
 	// Create two independent threads each of which will execute the function 
	// print_message_function, by passing a different string as the fourth parameter.
	// That is, the first thread has message1 as the fourth parameter, the second thread has
	// message2 as the fourth parameter

     if ( iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1))
	{
		printf("Thread creation failed: %d\n", iret1);
	}
     if ( iret2 = pthread_create( &thread2, NULL, print_message_function, (void*) message2))
	{
		printf("Thread creation failed: %d\n", iret2);
	}
 
     // Wait till threads are complete before main continues. Unless we  
     // wait we run the risk of executing an exit which will terminate   
     // the process and all threads before the threads have completed.

	
     // OPTIONAL: try to get the return state of threads using the second parameter of pthread_join, and print it

	void *j1ret, *j2ret;
     	pthread_join( thread1, &j1ret);
     	pthread_join( thread2, &j2ret);

     	printf("Thread 1 returns: %d\n", *(int*)j1ret);
     	printf("Thread 2 returns: %d\n", *(int*)j2ret);
	fflush(stdout);
}
 
void *print_message_function( void *ptr )
{
     char *message;
     message = (char *) ptr;
     int i;
     for (i=0; i < 10000; i++)
     {
	//print the message and flush output on the screen
     		printf("%s ", message);
     }

	// OPTIONAL: when exiting from the thread, 
	// use pthread_exit and properly set the error code, 
	// such that this value can be retrieved in the main thread 
	// when using the join function

	result = -1;
	pthread_exit((void*)&result);
}

