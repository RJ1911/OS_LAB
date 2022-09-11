/*
 * Team No : 02
 * Date - 29-08-2022
 *
 * -----------------------
 *Rimil Murmu     039
 *Rafson Jani(L)  008
 *Rajan Kumar     041
 *Pallabi Soren   010(L)
 * ------------------------
 *
 * Assignment Details : 
 * Creating Deadlock using thread programming in c
 *------------------------------------------------
 *
 * Input Required : <no input>
 *----------------------------
 * Compilation Command : gcc -pthread -o a assign05.c
 *-----------------------------------------------
 *
 * Output Generated :
 * -----------------
 * [be2004L@localhost ass_5]$ ./a
 *
 *
 * Created the threads
 *
 *
 * Thread1
 *
 * Thread2
 *
 * Total_1 : 985   Total_2 : 1015          Total_1 + Total_2 : 2000
 * Total_1 : 980   Total_2 : 1020          Total_1 + Total_2 : 2000
 *
 * Joined the thread
 *
 *
 *
 * Created the threads
 *
 *
 * Thread1
 *
 * Total_1 : 944   Total_2 : 1056          Total_1 + Total_2 : 2000
 * Thread2
 *
 * Total_1 : 941   Total_2 : 1059          Total_1 + Total_2 : 2000
 *
 * Joined the thread
 *
 *
 */



#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>

int Total_1 = 1000;
int Total_2 = 1000;

pthread_mutex_t mutex_1;
pthread_mutex_t mutex_2;

void *func1() {
	printf("\nThread1\n");
	pthread_mutex_lock(&mutex_1);
       // printf("\n\nThread 1 acquired mutex_1\n");
        pthread_mutex_lock(&mutex_2);
       // printf("\nThread 1 acquired mutex_2");
	int quantity_1;
	time_t t1;
	srand((unsigned) time(&t1));
	quantity_1 = rand() % 50 + 1;
	Total_1 -= quantity_1;
	Total_2 += quantity_1;
	printf("\nTotal_1 : %d\tTotal_2 : %d\t\tTotal_1 + Total_2 : %d", Total_1, Total_2, Total_1+Total_2);
        sleep(1);
        //printf("\n\nUnlocking both tht threads\n\n");
        pthread_mutex_unlock(&mutex_2);
        //printf("\nReleased thread 2\n");
        pthread_mutex_unlock(&mutex_1);
        //printf("\nReleased thread 1\n");
}
void *func2() {
	printf("\nThread2\n");
	pthread_mutex_lock(&mutex_2);
	//printf("\nThread 2 acquired mutex_2");
	 pthread_mutex_lock(&mutex_1);
        //printf("\n\nThread 2 acquired first mutex\n");
	int quantity_2;
	time_t t2;
	srand((unsigned) time(&t2));
	quantity_2 = rand() % 50 + 1;
	Total_1 -= quantity_2;
	Total_2 += quantity_2;
	printf("\nTotal_1 : %d\tTotal_2 : %d\t\tTotal_1 + Total_2 : %d", Total_1, Total_2, Total_1+Total_2);
	sleep(1);
	//printf("\n\nUnlocking both tht threads\n\n");
	pthread_mutex_unlock(&mutex_1);
	//printf("\nReleased thread 1\n");
	pthread_mutex_unlock(&mutex_2);
	//printf("\nReleased thread 2\n");
}

int main(int argc, char *argv[]) {
	while(1) {
	 //Initialize the lock
	pthread_mutex_init(&mutex_1, NULL);
	pthread_mutex_init(&mutex_2, NULL);
	
	//creating the thread
	pthread_t one, two;
	pthread_create(&one, NULL, func1, NULL);
	pthread_create(&two, NULL, func2, NULL);
	printf("\n\nCreated the threads\n\n");

	//Joining the thread
	pthread_join(one, NULL);
	pthread_join(two, NULL);
	printf("\n\nJoined the thread\n\n");
	}
	return 0;
}
