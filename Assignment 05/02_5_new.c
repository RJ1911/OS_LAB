#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

int Total_1 = 1000;
int Total_2 = 1000;

pthread_mutex_t mutex_1;
pthread_mutex_t mutex_2;


void printLine()
{
	printf("----------------------------------------------------------\n");
	return;
}

int randomNumberGenerator(int lowerCap, int higherCap)			// Generates a random number between lowerCap and higherCap
{
	int difference = higherCap - lowerCap;
	int randomNumber = lowerCap + rand() %  (higherCap - lowerCap + 1);

	return randomNumber;
}

void *getTheSums() 
{
	while(1)
	{
	printLine();

	printf("The CURRENT SUMS are : \n");
    	printf(" Total_1 : %d\n",Total_1);
	printf(" Total_2 : %d\n",Total_2);
	int totalSum = Total_1 + Total_2;
	printf(" Total1 + Total2 : %d\n",totalSum);

	printLine();
	}

	void *ptr;

	return ptr;
}

void *threadOne() 
{
 	while(1)
	{   
		pthread_mutex_lock(&mutex_1);                                                                                                                                                                                                                                                                                                                               pthread_mutex_lock(&mutex_2);        
	int randomNumber;
	time_t time1;
	
	srand((unsigned) time(&time1));
	
	randomNumber = randomNumberGenerator(0,10);
	Total_1 += randomNumber;
	Total_2 -= randomNumber;

       pthread_mutex_lock(&mutex_2);                                                                                                                                                                                                                                                                                                                               pthread_mutex_lock(&mutex_1);
        }
   // pthread_mutex_unlock(&mutex_2);
    
    //pthread_mutex_unlock(&mutex_1);

	void *ptr;

	return ptr;
}

void *threadTwo() 
{
	 while(1)
	{
		   pthread_mutex_lock(&mutex_2);                                                                                                                                                                                                                                                                                                                               pthread_mutex_lock(&mutex_1);
	int randomNumber;
	time_t time2;
	
	srand((unsigned) time(&time2));

	randomNumber = randomNumberGenerator(0,10);
	
	Total_1 -= randomNumber;
	Total_2 += randomNumber;

	        pthread_mutex_unlock(&mutex_1);                                                                                                                                                                                                                                                                                                                             pthread_mutex_unlock(&mutex_2); 
	}
	
	void *ptr;

	return ptr;
}

int main(int argc, char *argv[]) 
{													// Initializing the lock
    	pthread_mutex_init(&mutex_1, NULL);
    	pthread_mutex_init(&mutex_2, NULL);
    	
    	
    	pthread_t Th1, Th2, Th3;						// Creating the thread
    	pthread_create(&Th1, NULL, threadOne, NULL);
    	pthread_create(&Th2, NULL,  threadTwo, NULL);
    	pthread_create(&Th3, NULL, getTheSums, NULL);
    	
    	
    	pthread_join(Th1, NULL);						// Joining the thread
    	pthread_join(Th2, NULL);
    	pthread_join(Th3,NULL);
	
	return 0;
}
