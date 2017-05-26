#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <string.h>

struct leibniz_args { //arguments for leibniz function
    int start; // starting point of power of -1. It can be 0 or 1
    double denominator; // Starting denominator
    int iteration; // number of cycle(iteration)
};

void *leibniz(void *arguments);
double sum=0;
pthread_mutex_t locker; // mutex to prevent race condition when adding local sum to global

int main(int argc, char **argv)
{
	double pi;
	int n=1;
	int i;
	if (argc<3) //If arguments are not enough show usage.
	{
		printf("Usage: ./pi numberOfThreads numberOfIterations\n");
		return 0;
	}
	int nthreads = atoi(argv[1]);
	int iteration=atoi(argv[2]);
	pthread_t tHandles[nthreads];
	struct leibniz_args *args;
    pthread_mutex_init(&locker, NULL);
	
	for(i=0;i<nthreads;i++)
	{
		args = malloc(sizeof(struct leibniz_args)); // initialize new struct for every thread
		(*args).iteration = iteration/nthreads;
		n=1+(i*(*args).iteration); // n defined as index of leibniz series. It starts from 1.
		(*args).start=(n+1)%2;
		(*args).denominator=2*n-1;		
		pthread_create(&tHandles[i],           // Returned thread handle
                       NULL,                  // Thread Attributes
                       leibniz,              // Thread function
                       (void *)args);		//Function argument
	}
	for ( i = 0; i < nthreads; i++ ) 
	{
		pthread_join(tHandles[i], NULL); // wait for all thread
	}
	
	pi=sum*4;
	printf("%1.51f\n",pi);
	pthread_mutex_destroy(&locker);	
}

void *leibniz(void *arguments)
{
	struct leibniz_args *args = (struct leibniz_args*) arguments; 
	double localsum = 0;
	int i;
	double nom=1;
	for(i=(*args).start;i<(*args).iteration;i++)
	{
		localsum+=pow((-1),i)*(nom/(*args).denominator); // calculate elements of leibniz series and add to sum.
		(*args).denominator+=2; // increment deminator for next element
	}
	pthread_mutex_lock(&locker); // lock the mutex 
	sum+=localsum;				 // add local sum to global sum
	pthread_mutex_unlock(&locker); // unlock the mutex
	free(arguments); // free the arguments
}
