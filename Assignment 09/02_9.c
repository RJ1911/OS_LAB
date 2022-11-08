/*
     Group : A1
     Team Number : 02
     Date : 2nd November , 2022

         Name               Roll
     --------------------------------
     1. Rimil Murmu          039
     2. Rafson Jani (L)      008
     3. Rajan Kumar          041
     4. Pallabi Soren        010
*/

/*
    Assignment : 9 .Parallel Programming using THREAD

    Details:
    The objective of this assignment is to use thread programming technique to
write a parallel program which will do Matrix Multiplication between two
large Square Matrices with unsigned character elements. You have to also
measure the time elapsed. The Matrix should be large enough (dynamically
allocated) to fit in your computer memory. Both the Matrices need to be
initialized with random numbers (‘mod’ to some value).
As you increase the number of threads(max to your number of CPUs), your
timing should show improvement. Use ‘gettimeofday’ to note down the
timing. Make sure you attach the timing to the starting comment block of
your source file and also show the speedup. Your time should not include
the Matrices initialization time.
You have to use various ‘Pthread’ library calls to do this assignment
properly. Use the proper process listing command (ps) to show (and attach
it to the starting comment block of your source file) that your threads are
running in the system. Also, use proper command to show CPU and
Memory utilization and attach these outputs to the starting comment block
of your source file.
This program should take four command line arguments. The first
argument is the dimension of the Square Matrix.
The second argument is about the number of threads. For example, the
value of the second argument will be 1, 2, 3, and 4 etc.; signifying total no
of threads which will be created.
The third argument will be the value of the ‘mod’ which will be used to
initialize all the elements of two input square matrices.
The fourth (last) argument will be the print_switch. If its value is ‘1’, both the
Input and Output Matrices will be printed on the screen. In case the value is
‘0’, Matrices won’t be printed on the screen.


    Input Description:
    <No Input>

    Output Description:
    -> Print time Taken
    -> Print Matrices


*/

/*


    Compilation Command:
    gcc 02_9.c -o 02_9 -lpthread

    Execution Sequence:
    ./02_9 <dimension> <no of threads> <value of MOD> <print switch>

*/

/*

    Sample Input :
    <No input>

    Sample Output :
    wsl_ubuntu@RJ:~$ ./a.out 3 3 10 1
Time Taken = 0.000001

Matrix 1 :

0 1 9
3 1 8
6 7 3
Matrix 2 :

8 0 1
5 9 0
1 3 4
Result :

14 36 36
37 33 35
86 72 18



wsl_ubuntu@RJ:~$ ./a.out 100 20 10 0
Time Taken = 0.023582

wsl_ubuntu@RJ:~$ ./a.out 1000 20 10 0
Time Taken = 223.533707

// Threads running
wsl_ubuntu@RJ:~$ ps -elf
F S UID        PID  PPID  C PRI  NI ADDR SZ WCHAN  STIME TTY          TIME CMD
0 S wsl_ubu+   165    33  0  80   0 -  2538 core_s 15:15 pts/3    00:00:00 /usr/bin/bash --init-file /home/wsl_ubuntu/.vscode-server/bin/d045a5e
0 S wsl_ubu+   220    33  0  80   0 -  2538 core_s 15:46 pts/4    00:00:00 /usr/bin/bash --init-file /home/wsl_ubuntu/.vscode-server/bin/d045a5e
0 S wsl_ubu+   274    33  0  80   0 -  2538 core_s 16:10 pts/5    00:00:00 /usr/bin/bash --init-file /home/wsl_ubuntu/.vscode-server/bin/d045a5e
5 S root      2132     1  0  80   0 -   707 -      16:49 ?        00:00:00 /init
5 S root      2133  2132  0  80   0 -   711 -      16:49 ?        00:00:00 /init
4 S wsl_ubu+  2134  2133  0  80   0 -  2514 do_wai 16:49 pts/6    00:00:00 -bash
5 S root      2452     1  0  80   0 -   707 -      16:52 ?        00:00:00 /init
5 S root      2453  2452  0  80   0 -   711 -      16:52 ?        00:00:00 /init
4 S wsl_ubu+  2454  2453  0  80   0 -  2514 do_wai 16:52 pts/7    00:00:00 -bash
0 R wsl_ubu+  2670  2134 99  80   0 - 98356 -      17:04 pts/6    00:00:44 ./a.out 10000 200 10 0
0 R wsl_ubu+  2673  2454  0  80   0 -  2654 -      17:04 pts/7    00:00:00 ps -elf


// Memory Usage :

        top - 17:06:38 up  2:15,  0 users,  load average: 0.97, 0.97, 0.65
Tasks:  28 total,   3 running,  25 sleeping,   0 stopped,   0 zombie
%Cpu(s):  3.8 us, 21.0 sy,  0.0 ni, 72.2 id,  1.1 wa,  0.0 hi,  1.8 si,  0.0 st
MiB Mem :   3802.8 total,   2914.4 free,    533.2 used,    355.2 buff/cache
MiB Swap:   1024.0 total,   1024.0 free,      0.0 used.   3057.1 avail Mem

  PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND
 2676 wsl_ubu+  20   0   49620  41880   1192 R 100.0   1.1   0:09.52 a.out
   99 wsl_ubu+  20   0  680504  90536  35700 R   0.3   2.3   1:03.84 node
    1 root      20   0    2456   1776   1692 S   0.0   0.0   0:01.07 init
   10 root      20   0    2428    112      0 S   0.0   0.0   0:00.00 init
   11 root      20   0    2428    120      0 S   0.0   0.0   0:00.02 init
   12 wsl_ubu+  20   0    2612    528    456 S   0.0   0.0   0:00.05 sh
   13 wsl_ubu+  20   0    2612    588    520 S   0.0   0.0   0:00.01 sh
   18 wsl_ubu+  20   0    2612    592    524 S   0.0   0.0   0:00.00 sh
   22 wsl_ubu+  20   0  932276  76300  34712 S   0.0   2.0   1:08.88 node
   33 wsl_ubu+  20   0  724120  59032  32448 S   0.0   1.5   0:25.48 node
   42 root      20   0    2420    112      0 S   0.0   0.0   0:00.00 init
   43 root      20   0    2436    120      0 S   0.0   0.0   0:02.44 init
   44 wsl_ubu+  20   0  587480  46220  29540 S   0.0   1.2   0:08.87 node
   75 root      20   0    2420    112      0 S   0.0   0.0   0:00.00 init
   76 root      20   0    2436    120      0 S   0.0   0.0   0:05.96 init
   77 wsl_ubu+  20   0  589228  44920  29520 S   0.0   1.2   0:17.90 node
   86 wsl_ubu+  20   0  835504  47084  31772 S   0.0   1.2   0:12.70 node
  158 wsl_ubu+  20   0  590192  47384  31668 S   0.0   1.2   0:02.63 node
  165 wsl_ubu+  20   0   10152   5228   3432 S   0.0   0.1   0:00.28 bash
  220 wsl_ubu+  20   0   10152   5164   3368 S   0.0   0.1   0:00.25 bash
  274 wsl_ubu+  20   0   10152   5260   3468 S   0.0   0.1   0:00.42 bash
 2132 root      20   0    2828    392      0 S   0.0   0.0   0:00.00 init
 2133 root      20   0    2844    396      0 S   0.0   0.0   0:00.07 init
 2134 wsl_ubu+  20   0   10056   5140   3376 S   0.0   0.1   0:00.36 bash
 2452 root      20   0    2828    392      0 S   0.0   0.0   0:00.00 init
 2453 root      20   0    2844    396      0 S   0.0   0.0   0:00.07 init
 2454 wsl_ubu+  20   0   10056   5060   3296 S   0.0   0.1   0:00.31 bash
 2675 wsl_ubu+  20   0   10880   3560   3036 R   0.0   0.1   0:00.02 top

 // Memory Usgae

 top - 17:07:48 up  2:16,  0 users,  load average: 132.61, 39.73, 14.06
Tasks:  28 total,   1 running,  27 sleeping,   0 stopped,   0 zombie
%Cpu(s): 98.8 us,  0.9 sy,  0.0 ni,  0.0 id,  0.0 wa,  0.0 hi,  0.2 si,  0.0 st
MiB Mem :   3802.8 total,   2896.5 free,    550.9 used,    355.4 buff/cache
MiB Swap:   1024.0 total,   1024.0 free,      0.0 used.   3039.3 avail Mem

  PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND
 2676 wsl_ubu+  20   0 1688820  49800   1192 S 396.1   1.3   4:32.93 ./a.out 2000 200 10 0
   99 wsl_ubu+  20   0  680504  90560  35700 S   1.0   2.3   1:04.59 /home/wsl_ubuntu/.vscode-server/bin/d045a5eda657f4d7b676dedbfa7aab8207f8a+
   33 wsl_ubu+  20   0  724120  59296  32448 S   0.6   1.5   0:25.87 /home/wsl_ubuntu/.vscode-server/bin/d045a5eda657f4d7b676dedbfa7aab8207f8a+
  158 wsl_ubu+  20   0  590192  47640  31668 S   0.3   1.2   0:02.65 /home/wsl_ubuntu/.vscode-server/bin/d045a5eda657f4d7b676dedbfa7aab8207f8a+
 2453 root      20   0    2844    396      0 S   0.3   0.0   0:00.08 /init
    1 root      20   0    2456   1776   1692 S   0.0   0.0   0:01.07 /init
   10 root      20   0    2428    112      0 S   0.0   0.0   0:00.00 /init
   11 root      20   0    2428    120      0 S   0.0   0.0   0:00.02 /init
   12 wsl_ubu+  20   0    2612    528    456 S   0.0   0.0   0:00.05 sh -c "$VSCODE_WSL_EXT_LOCATION/scripts/wslServer.sh" d045a5eda657f4d7b67+
   13 wsl_ubu+  20   0    2612    588    520 S   0.0   0.0   0:00.01 sh /mnt/c/Users/RAFSON/.vscode/extensions/ms-vscode-remote.remote-wsl-0.7+
   18 wsl_ubu+  20   0    2612    592    524 S   0.0   0.0   0:00.00 sh /home/wsl_ubuntu/.vscode-server/bin/d045a5eda657f4d7b676dedbfa7aab8207+
   22 wsl_ubu+  20   0  932276  76748  34712 S   0.0   2.0   1:09.29 /home/wsl_ubuntu/.vscode-server/bin/d045a5eda657f4d7b676dedbfa7aab8207f8a+
   42 root      20   0    2420    112      0 S   0.0   0.0   0:00.00 /init
   43 root      20   0    2436    120      0 S   0.0   0.0   0:02.47 /init
   44 wsl_ubu+  20   0  587480  46220  29540 S   0.0   1.2   0:08.98 /home/wsl_ubuntu/.vscode-server/bin/d045a5eda657f4d7b676dedbfa7aab8207f8a+
   75 root      20   0    2420    112      0 S   0.0   0.0   0:00.00 /init
   76 root      20   0    2436    120      0 S   0.0   0.0   0:05.99 /init
   77 wsl_ubu+  20   0  589364  45184  29520 S   0.0   1.2   0:17.99 /home/wsl_ubuntu/.vscode-server/bin/d045a5eda657f4d7b676dedbfa7aab8207f8a+
   86 wsl_ubu+  20   0  835504  46752  31772 S   0.0   1.2   0:12.83 /home/wsl_ubuntu/.vscode-server/bin/d045a5eda657f4d7b676dedbfa7aab8207f8a+   165 wsl_ubu+  20   0   10152   5228   3432 S   0.0   0.1   0:00.28 /usr/bin/bash --init-file /home/wsl_ubuntu/.vscode-server/bin/d045a5eda65+
  220 wsl_ubu+  20   0   10152   5164   3368 S   0.0   0.1   0:00.25 /usr/bin/bash --init-file /home/wsl_ubuntu/.vscode-server/bin/d045a5eda65+
  274 wsl_ubu+  20   0   10152   5260   3468 S   0.0   0.1   0:00.42 /usr/bin/bash --init-file /home/wsl_ubuntu/.vscode-server/bin/d045a5eda65+
 2132 root      20   0    2828    392      0 S   0.0   0.0   0:00.00 /init
 2133 root      20   0    2844    396      0 S   0.0   0.0   0:00.07 /init
 2134 wsl_ubu+  20   0   10056   5140   3376 S   0.0   0.1   0:00.36 -bash
 2452 root      20   0    2828    392      0 S   0.0   0.0   0:00.00 /init
 2454 wsl_ubu+  20   0   10056   5060   3296 S   0.0   0.1   0:00.31 -bash
 2675 wsl_ubu+  20   0   10880   3560   3036 R   0.0   0.1   0:00.14 top

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <time.h>
#include <sys/random.h>
#include <sys/time.h>

#define max_thread 1000

int threadCount = 0;
int dimension = 0;
int modValue = 0;
int print_switch = 0;
int **matrix1;
int **matrix2;
int **result;
float total_time = 0;

int **create_matrix(int n);
void print_matrix(int **arr);

void *multi(void *arg)
{
    // Timer
    struct timeval start, end;

    // start timer.
    gettimeofday(&start, NULL);

    long int threadNumber = (long int)arg;
    int i, j, k;

    int from = (threadNumber * dimension) / threadCount;
    int to = ((threadNumber + 1) * dimension) / threadCount;

    for (int i = from; i < to; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < dimension; k++)
            {
                result[i][j] += (matrix1[i][k] * matrix2[k][j]);
            }
        }
    }

    // Timer Stops
    gettimeofday(&end, NULL);

    // Calculating total time taken by the program.
    double time_taken;

    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec -
                                start.tv_usec)) *
                 1e-6;
    total_time += time_taken;
}

int main(int argc, char *argv[])
{

    if (argc != 5)
    {
        printf("Please input correct arguments\n");
        exit(0);
    }

    dimension = atoi(argv[1]);
    threadCount = atoi(argv[2]);
    modValue = atoi(argv[3]);
    print_switch = atoi(argv[4]);

    pthread_t tid[max_thread];
    long int i, j;

    matrix1 = create_matrix(dimension);
    matrix2 = create_matrix(dimension);

    result = create_matrix(dimension);

    // Creating threads
    for (i = 0; i < threadCount; i++)
    {
        if (pthread_create(&tid[i], NULL, &multi, (void *)i) != 0)
        {
            perror("Could not create Thread\n");
            exit(0);
        }
    }

    // Joining Threads
    for (j = 0; j < threadCount; j++)
    {
        if (pthread_join(tid[j], NULL) != 0)
        {
            perror("Could not join Thread \n");
            exit(0);
        }
    }

    printf("Time Taken = %f \n", total_time);

    if (print_switch == 1)
    {
        printf("\nMatrix 1 : \n");
        print_matrix(matrix1);
        printf("Matrix 2 : \n");
        print_matrix(matrix2);
        printf("Result : \n");
        print_matrix(result);
    }

    free(matrix1);
    free(matrix2);
    free(result);

    return 0;
}

int **create_matrix(int n)
{
    int r = n, c = n, i, j;

    int **arr = (int **)malloc(r * sizeof(int *));
    for (i = 0; i < r; i++)
        arr[i] = (int *)malloc(c * sizeof(int));

    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
        {
            // Generate Random Number
            int randomNumber;
            if (getrandom(&randomNumber, sizeof(int), GRND_NONBLOCK) == -1)
            {
                perror("getrandom():");
                exit(1);
            }
            if (randomNumber < 0)
            {
                randomNumber *= -1;
            }
            arr[i][j] = randomNumber % modValue;
        }

    return arr;
}

void print_matrix(int **arr)
{
    int i, j;
    int r = dimension;
    int c = dimension;
    for (i = 0; i < r; i++)
    {
        printf("\n");
        for (j = 0; j < c; j++)
            printf("%d ", arr[i][j]);
    }
    printf("\n");
}