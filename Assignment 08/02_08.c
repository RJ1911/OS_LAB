/*
	 Group : A1
	 Team Number : 02
	 Date : 21st October , 2022
		 Name               Roll
	 --------------------------------
	 1. Rimil Murmu          039
	 2. Rafson Jani (L)      008
	 3. Rajan Kumar          041
	 4. Pallabi Soren        010
*/

/*
	Assignment : 8 . Thread Programming Using Queue
	Details:
	Consider a process with three threads A, B, and C. The default thread of the process receives two inputs (X, Y) and places them in a queue that is accessible by all the three threads A, B and C. For each pair of input (X,Y), we require that the request must first be processed by thread A (Multiplication (X*Y)),then B(Division (X*Y)/2), then C (Addition (X+Y)), then B again ( (X*Y) /(X+Y)), and finally by A((X+Y)* (X+Y)) before the pair (X,Y) can be removed and discarded from the queue.
	Thread A must read the next request from the queue only after it is finished with all the above steps of the previous one. Write down code for the functions run by the threads A, B, and C, to enable this synchronization. You may use any synchronization primitive of your choice to solve this question.

	Input Description:
	<N, number of random pairs>

	Output Description:
	[Initial Queue]
	Operations performed by threads A,B and C.

*/

/*
	Compilation Command:
	gcc 02_08.c -o 02_08 -lpthread

	Execution Sequence:
	./02_08
*/

/*
	Sample Input :
	Enter count of inputs : 5

	Enter pair 1 :
		Enter X : 1
		Enter Y : 1

	Enter pair 2 :
		Enter X : 2
		Enter Y : 2

	Enter pair 3 :
		Enter X : 3
		Enter Y : 3

	Enter pair 4 :
		Enter X : 4
		Enter Y : 4

	Enter pair 5 :
		Enter X : 5
		Enter Y : 5

	Sample Output :

	Current Queue :  (1,1)  (2,2)  (3,3)  (4,4)  (5,5)

	Processing input (X,Y) =  (1,1) :
	Operation 1 (X*Y) => Processed by Thread A : (1*1) = 1
	Operation 2 (X*Y)/2 => Processed by Thread B : ((1*1)/2) = 0
	Operation 3 (X+Y) => Processed by Thread C : (1+1) = 2
	Operation 4 (X*Y)/(X+Y) => Processed by Thread B : ((1*1)/(1+1)) = 0
	Operation 5 (X+Y)*(X+Y) => Processed by Thread A : ((1+1)*(1+1)) = 4
	(1,1) discarded from Queue

	Current Queue :  (2,2)  (3,3)  (4,4)  (5,5)

	Processing input (X,Y) =  (2,2) :
	Operation 1 (X*Y) => Processed by Thread A : (2*2) = 4
	Operation 2 (X*Y)/2 => Processed by Thread B : ((2*2)/2) = 2
	Operation 3 (X+Y) => Processed by Thread C : (2+2) = 4
	Operation 4 (X*Y)/(X+Y) => Processed by Thread B : ((2*2)/(2+2)) = 1
	Operation 5 (X+Y)*(X+Y) => Processed by Thread A : ((2+2)*(2+2)) = 16
	(2,2) discarded from Queue

	Current Queue :  (3,3)  (4,4)  (5,5)

	Processing input (X,Y) =  (3,3) :
	Operation 1 (X*Y) => Processed by Thread A : (3*3) = 9
	Operation 2 (X*Y)/2 => Processed by Thread B : ((3*3)/2) = 4
	Operation 3 (X+Y) => Processed by Thread C : (3+3) = 6
	Operation 4 (X*Y)/(X+Y) => Processed by Thread B : ((3*3)/(3+3)) = 1
	Operation 5 (X+Y)*(X+Y) => Processed by Thread A : ((3+3)*(3+3)) = 36
	(3,3) discarded from Queue

	Current Queue :  (4,4)  (5,5)

	Processing input (X,Y) =  (4,4) :
	Operation 1 (X*Y) => Processed by Thread A : (4*4) = 16
	Operation 2 (X*Y)/2 => Processed by Thread B : ((4*4)/2) = 8
	Operation 3 (X+Y) => Processed by Thread C : (4+4) = 8
	Operation 4 (X*Y)/(X+Y) => Processed by Thread B : ((4*4)/(4+4)) = 2
	Operation 5 (X+Y)*(X+Y) => Processed by Thread A : ((4+4)*(4+4)) = 64
	(4,4) discarded from Queue

	Current Queue :  (5,5)

	Processing input (X,Y) =  (5,5) :
	Operation 1 (X*Y) => Processed by Thread A : (5*5) = 25
	Operation 2 (X*Y)/2 => Processed by Thread B : ((5*5)/2) = 12
	Operation 3 (X+Y) => Processed by Thread C : (5+5) = 10
	Operation 4 (X*Y)/(X+Y) => Processed by Thread B : ((5*5)/(5+5)) = 2
	Operation 5 (X+Y)*(X+Y) => Processed by Thread A : ((5+5)*(5+5)) = 100
	(5,5) discarded from Queue

	Current Queue :

	Queue Empty!!!
	All inputs processed.

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/******************************* Queue implementation using Linked List ******************************************************/
// A linked list (LL) node to store a queue entry
struct QueueNode
{
	int data1;
	int data2;
	struct QueueNode *next;
};

// The queue, front stores the front node of LL and rear stores the last node of LL
struct Queue
{
	struct QueueNode *front, *rear;
};

// A utility function to create a new linked list node.
struct QueueNode *newQueueNode(int x, int y)
{
	struct QueueNode *temp = (struct QueueNode *)malloc(sizeof(struct QueueNode));
	temp->data1 = x;
	temp->data2 = y;
	temp->next = NULL;
	return temp;
}

// A utility function to create an empty queue
struct Queue *createQueue()
{
	struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
	q->front = q->rear = NULL;
	return q;
}

// The function to add data to q
void enQueue(struct Queue *q, int x, int y)
{
	// Create a new LL node
	struct QueueNode *temp = newQueueNode(x, y);

	// If queue is empty, then new node is front and rear
	// both
	if (q->rear == NULL)
	{
		q->front = q->rear = temp;
		return;
	}

	// Add the new node at the end of queue and change rear
	q->rear->next = temp;
	q->rear = temp;
}

// Function to remove data from given queue q
void deQueue(struct Queue *q)
{
	// If queue is empty, return NULL.
	if (q->front == NULL)
		return;

	// Store previous front and move front one node ahead
	struct QueueNode *temp = q->front;

	q->front = q->front->next;

	// If front becomes NULL, then change rear also as NULL
	if (q->front == NULL)
		q->rear = NULL;

	free(temp);
}

struct Queue *q; // Global Queue

pthread_mutex_t lock;

/****************************** Thread Functions Implementaion  *************************************************************************/

int taskNo = 1; // value of taskNo decides which thread will access queue and other threads will wait .
/*
	taskNo = 1 => Thread A Operation (X*Y)
	taskNo = 2 => Thread B Operation (X*Y)/2
	taskNo = 3 => Thread C Operation (X+Y)
	taskNo = 4 => Thread A Operation (X*Y)/(X+Y)
	taskNo = 5 => Thread A Operation (X+Y)*(X+Y)
*/

/* function called by thread A */
void *function_thread_A(void *args)
{
	while (q->front != NULL)
	{
		while ((taskNo == 1 || taskNo == 5))
		{
			if (taskNo == 1) // Thread A Operation (X*Y)
			{
				pthread_mutex_lock(&lock); // Thread A accessing Queue and performing Operation 1 , rest threads waiting.
				struct Queue *q = (struct Queue *)args;
				struct QueueNode *temp = q->front;
				printf("Current Queue : ");
				while (temp != NULL)
				{
					printf(" (%d,%d) ", temp->data1, temp->data2);
					temp = temp->next;
				}
				printf("\n\n");
				if (q->front == NULL)
				{
					printf("Queue Empty!!!\nAll inputs processed.\n");
					exit(0);
				}
				int x = q->front->data1;
				int y = q->front->data2;
				printf("Processing input (X,Y) =  (%d,%d) : \n", x, y);
				int result = x * y;
				printf("  Operation 1 (X*Y) => Processed by Thread A : (%d*%d) = %d \n", x, y, result);
				taskNo = 2;
				pthread_mutex_unlock(&lock);
			}
			else if (taskNo == 5) // Thread A Operation (X+Y)*(X+Y)
			{
				pthread_mutex_lock(&lock);// Thread A accessing Queue and performing Operation 5 , rest threads waiting.
				struct Queue *q = (struct Queue *)args;

				int x = q->front->data1;
				int y = q->front->data2;
				int result = (x + y) * (x + y);
				printf("  Operation 5 (X+Y)*(X+Y) => Processed by Thread A : ((%d+%d)*(%d+%d)) = %d \n", x, y, x, y, result);
				printf(" (%d,%d) discarded from Queue\n\n", x, y);
				deQueue(q); // Dequeing after front input is processed.
				taskNo = 1;
				pthread_mutex_unlock(&lock);
			}
		}
	}
}

/* function called by thread B */
void *function_thread_B(void *args)
{
	while (q->front != NULL)
	{
		while ((taskNo == 2 || taskNo == 4))
		{
			if (taskNo == 2) // Thread B Operation (X*Y)/2
			{
				pthread_mutex_lock(&lock); // Thread B accessing Queue and performing Operation 2 , rest threads waiting.
				struct Queue *q = (struct Queue *)args;
				int x = q->front->data1;
				int y = q->front->data2;
				int result = (x * y) / 2;
				;
				printf("  Operation 2 (X*Y)/2 => Processed by Thread B : ((%d*%d)/2) = %d \n", x, y, result);
				taskNo = 3;
				pthread_mutex_unlock(&lock);
			}
			else if (taskNo == 4) // Thread A Operation (X*Y)/(X+Y)
			{
				pthread_mutex_lock(&lock); // Thread B accessing Queue and performing Operation 4 , rest threads waiting.
				struct Queue *q = (struct Queue *)args;

				int x = q->front->data1;
				int y = q->front->data2;
				int result = 0;
				if ((x + y) == 0)
				{
					printf("  Operation 4 (X*Y)/(X+Y) => Processed by Thread B : (%d*%d)/(%d+%d) = undefined \n", x, y, x, y);
				}
				else
				{
					result = (x * y) / (x + y);
					printf("  Operation 4 (X*Y)/(X+Y) => Processed by Thread B : ((%d*%d)/(%d+%d)) = %d \n", x, y, x, y, result);
				}
				taskNo = 5;
				pthread_mutex_unlock(&lock);
			}
		}
	}
}

/* function called by thread C */
void *function_thread_C(void *args)
{
	while (q->front != NULL)
	{
		while (taskNo == 3) // Thread C Operation (X+Y)
		{
			pthread_mutex_lock(&lock); // Thread C accessing Queue and performing Operation 3 , rest threads waiting.
			struct Queue *q = (struct Queue *)args;
			int x = q->front->data1;
			int y = q->front->data2;
			int result = x + y;
			printf("  Operation 3 (X+Y) => Processed by Thread C : (%d)+(%d) = %d \n", x, y, result);
			taskNo = 4;
			pthread_mutex_unlock(&lock);
		}
	}
}
/********************Driver Program*********************************************************************/
int main()
{
	// initializing queue
	q = createQueue();
	int N = 0;

	/*  Taking Input */
	printf("Enter count of inputs : ");
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
	{
		int x, y;
		printf("\nEnter pair %d : ", i);
		printf("\n\tEnter X : ");
		scanf("%d", &x);
		printf("\tEnter Y : ");
		scanf("%d", &y);
		enQueue(q, x, y);
	}

	printf("\n");

	// declaring thread variables
	pthread_t A, B, C;

	pthread_mutex_init(&lock, NULL);

	// Creating threads
	if (pthread_create(&A, NULL, &function_thread_A, (void *)q) != 0)
	{
		perror("Could not create Thread A \n)");
		exit(0);
	}
	if (pthread_create(&B, NULL, &function_thread_B, (void *)q) != 0)
	{
		perror("Could not create Thread B \n)");
		exit(0);
	}
	if (pthread_create(&C, NULL, &function_thread_C, (void *)q) != 0)
	{
		perror("Could not create Thread C \n)");
		exit(0);
	}

	// Joining Threads to main()
	if (pthread_join(C, NULL) != 0)
	{
		perror("Could not join Thread A \n)");
		exit(0);
	}
	if (pthread_join(B, NULL) != 0)
	{
		perror("Could not join Thread B \n)");
		exit(0);
	}
	if (pthread_join(A, NULL) != 0)
	{
		perror("Could not join Thread C \n)");
		exit(0);
	}

	pthread_mutex_destroy(&lock);

	return 0;
}
