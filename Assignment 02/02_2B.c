/*
     Group : A1
     Team Number : 02
     Date : 3rd August , 2022

         Name               Roll
     --------------------------------
     1. Rimil Murmu          039
     2. Rafson Jani          008
     3. Rajan Kumar          041
     4. Pallabi Soren        010
*/

/*
    Assignment : 2-B . IPC using Named Pipe (FIFO)

    Details:  Create two processes. Transfer 1GB file from process1 to process2 using a
    FIFO. Now, transfer the same file from process2 to process1 using another
    FIFO. Now, compare the two files to make sure that the same file has returned
    back. Also, print the time required to do this double transfer. Attach this output
    to the source file as a comment.

    Input Description:
    <No Input>

    Output Description:

    Total Time Required to transfer files .


*/

/*
    Creating file of 1 GB size by using "fallocate" command :

      fallocate -l 1G dummy_file.txt

    Displaying created dummy_file.txt using "ls -l dummy_file.txt" command :

      -rw-r--r-- 1 rj rj 1073741824 Aug  3 18:43 dummy_file.txt

*/

/*
    Compilation Command:
    gcc 02_2B.c -o 02_2B

    Execution Sequence:
    ./02_2B "dummy_file.txt"

*/

/*
    Sample Input :
    <No Input>

    Sample Output :

        Transferring file from Process 1 to Process 2....

    File Transfer from Process 1 to Process 2 has finished.
    Time Taken : 10.244850 seconds .

        Transferring file from Process 2 to Process 1....

    File Transfer from Process2 to Process1 has finished.
    Time Taken : 12.626304 seconds .

    Both Transfers has finished!
    Time required for both transfers to complete : 22.871154 seconds .

         Comparing contents of recieved file and original source file....

    The contents of sent and received files were identical.

    Succesful File Transfer using FIFO.
    
    IPC using FIFO Successful!.

*/

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO1 "FIFO1" // naming of first named pipe
#define FIFO2 "FIFO2" // naming of second named pipe

#define BUFFER_FILE1 "process1_buffer" // the file received by process 1 is stored temporarily in this buffer
#define BUFFER_FILE2 "process2_buffer" // the file received by process 2 is stored temporarily in this buffer
#define BUFF_SIZE 1024                 // size of temprorary buffer to hold our 1GB sized file
#define FIFO_MODE 0666                 // permission to Read or  Write for everyone

/* Defining character Buffers to hold files temprorarily , which will be used in comparing the files while authenticating */
char buffer[BUFF_SIZE + 1];
char buffer2[BUFF_SIZE + 1];

/* Defining authenticate() funtion to check wether the contents of file1 is same as the contents of file2 */

bool authenticate(char *file1, char *file2)
{
    /* Opening first file in read mode */
    int fd1 = open(file1, O_RDONLY);
    if (fd1 == -1)
    {
        perror("Unable to open file.");
        exit(EXIT_FAILURE);
    }

    /* Opening second file in read mode */
    int fd2 = open(file2, O_RDONLY);
    if (fd2 == -1)
    {
        perror("Unable to open file.");
        exit(EXIT_FAILURE);
    }

    /* Comparing buffer by buffer contents of first file and second file */
    while (1)
    {
        /* Calling read function to read from first file , BUFF_SIZE of bytes of input into the memory area indicated by buffer */
        int length1 = read(fd1, buffer, BUFF_SIZE);

        /* Calling read function to read from second file , BUFF_SIZE of bytes of input into the memory area indicated by buffer2 */
        int length2 = read(fd2, buffer2, BUFF_SIZE);

        if (length1 != length2)
        {
            /* Files are of different size , which implies there content is not same */
            return false;
        }

        if (length1 == -1)
        {
            close(fd1);
            close(fd2);
            perror("Unable to Read the file!");
            exit(EXIT_FAILURE);
        }

        else if (length1 == 0)
        {
            /* Reached end of the file */
            return true;
        }

        else if (length1 > 0)
        {
            for (int i = 0; i < length1; i++)
            {
                if (buffer[length1] != buffer2[length2])
                    return false;
            }
        }
    }

    /* Full Comparison Completed , there is no error in between , hence contents of both files are same */
    return true;
}

/* Defining fileTransfer() function to transfer file from one process to another */
void fileTransfer(char *file1, char *file2, char *msg)
{
    /* Opening file to be transferred in read only mode */
    int fd1 = open(file1, O_RDONLY);

    if (fd1 == -1)
    {
        perror("Could not open the file!!");
        exit(EXIT_FAILURE);
    }

    /* Opening reciever file or creating a reciever file if it doesnt already exists in FIFO mode */
    int fd2 = open(file2, O_WRONLY | O_CREAT, FIFO_MODE);
    if (fd2 == -1)
    {
        perror("Could not open the file!!");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        /* Reading from FIFO. Reading BUFF_SIZE characters at a time */
        int length = read(fd1, buffer, BUFF_SIZE);

        if (length == -1)
        {
            close(fd1);
            close(fd2);
            perror("Could not read the file");
            exit(EXIT_FAILURE);
        }
        else if (length == 0)
        {
            /* Reached end of file(EOF) */
            break;
        }
        else if (length > 0)
        {
            /* Writing contents of sender file into reciever file */
            write(fd2, buffer, length);
        }
    }
    /* Closing the files after successful transfer */
    close(fd1);
    close(fd2);
}

/* Helper function for Process 1*/
/* To be called from Process 1 , for sending file to Process 2 via FIFO1 and recieve the same file from Process 2 via FIFO 2 */
void process1(char *inputFilePath)
{

    /* Transfer source file from Process 1 to Process 2 using FIFO1 */
    printf("\n     Transferring file from Process 1 to Process 2....\n");

    double first_transfer_time = 0.0;
    /* Timer Starts */
    clock_t begin1 = clock();

    fileTransfer(inputFilePath, FIFO1, "p1");

    clock_t end1 = clock();
    /* Timer Ends */

    first_transfer_time += (double)(end1 - begin1) / CLOCKS_PER_SEC;
    printf("\nFile Transfer from Process 1 to Process 2 has finished.\n");
    printf("Time Taken : %f seconds . \n", first_transfer_time);

    /* Recieving  file from Process 2 to Process 1 using FIFO2 */
    printf("\n     Transferring file from Process 2 to Process 1....\n");

    double second_transfer_time = 0.0;

    /* Timer Starts */
    clock_t begin2 = clock();

    fileTransfer(FIFO2, BUFFER_FILE1, "p1");

    clock_t end2 = clock();
    /*Timer Ends */

    second_transfer_time += (double)(end2 - begin2) / CLOCKS_PER_SEC;
    printf("\nFile Transfer from Process2 to Process1 has finished.\n");
    printf("Time Taken : %f seconds . \n", second_transfer_time);

    printf("\nBoth Transfers has finished!\n");
    printf("Time required for both transfers to complete : %f seconds .\n", first_transfer_time + second_transfer_time);

    /* Using authenticate() for comparing the contents of final recieved file and source file */
    printf("\n     Comparing contents of recieved file and original source file....\n");

    bool files_identical = authenticate(inputFilePath, BUFFER_FILE1);

    if (files_identical == true)
    {
        printf("The sent and received files were identical.\n\nIPC using FIFO Successful!.\n");
    }
    else
    {
        printf("\nError : Files are not identical !!!\n");
    }
}

/* Helper function for process 2 */
/* To recieve file from process 1 via FIFO1 and send it back to process 1 via FIFO2 */
void process2(void)
{
    /* Recieving file from process 1 to process 2 through FIFO1 , contents will be stored in BUFFER_FILE2 */
    fileTransfer(FIFO1, BUFFER_FILE2, "p2");

    /* Transferring files from process 2 to process 1  through FIFO2 */
    fileTransfer(BUFFER_FILE2, FIFO2, "p2");
}

int main(int argc, char *argv[])
{
    // CHECK IF FILE PATH IS INPUTTED
    if (argc != 2)
    {
        printf("Provide the path of the file to be transferred along with execution command \n");
        return EXIT_FAILURE;
    }

    /* Source file path of 1GB file to be transferred */
    char *inputFilePath = argv[1];

    /*Creating FIFO1 for file transfer from process 1 to process 2 */
    int fifo1 = mkfifo(FIFO1, FIFO_MODE);
    if (fifo1 < 0)
    {
        perror("Unable to create new FIFO1 .");
    }

    /*Creating FIFO2 for file transfer from process 2 to process 1 */
    int fifo2 = mkfifo(FIFO2, FIFO_MODE);
    if (fifo2 < 0)
    {
        perror("Unable to create new FIFO2 .");
    }

    /* Forking to create two processes , in between them files will be transferred */
    pid_t fid = fork();

    /* Unable to fork */
    if (fid == -1)
    {
        perror("Unable to fork\n");
        return EXIT_FAILURE;
    }

    /* fork() returned 0  , which implies child process */
    else if (fid == 0)
    {
        /* Considering child process as  process 2 */
        process2();
    }

    /* fork() returned greater than 0  , which implies parent  process */
    else if (fid > 0)
    {
        /* Considering parent process as process 1 */
        process1(inputFilePath);
    }
}
