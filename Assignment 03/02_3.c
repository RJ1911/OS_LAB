/*
     Group : A1
     Team Number : 02
     Date : 12th August , 2022

         Name               Roll
     --------------------------------
     1. Rimil Murmu          039
     2. Rafson Jani (L)      008
     3. Rajan Kumar          041
     4. Pallabi Soren        010
*/

/*
    Assignment : 3.Socket Programming

    Details:
    Create two processes. Transfer 1GB file from process1 to process2 using a
    Socket. Now, transfer that file from process2 to process1 using the same
    Socket.
    Now, compare the two files to make sure that the same file has returned back.
    Also, print the time required to do this double transfer. Attach this output to the
    source file as a comment.
    Please note that, you can see the socket which your program creates. There
    are also various bash shell commands available to see the sockets created by
    the program. So, once your program creates the socket, make sure you use
    proper command to see the socket info and paste that output as a comment in
    your source file.

    Input Description:
    <No Input>

    Output Description:
    Time required to do the double transfer .



*/
/*
    Compilation Command:
    gcc 02_3.c -o 02_3

    Execution Sequence:
    ./02_3 "test_file"

*/
/*
    ============================Creating 1GB sized file===============================
    Bash Command : fallocate -l 1G test_file

    rj@RJ:~/assignment03$ fallocate -l 1G test_file
    rj@RJ:~/assignment03$ ls -la
    total 1048608                                                                   
    drwxr-xr-x  2 rj rj       4096 Aug 12 19:59 .
    drwxr-xr-x 10 rj rj       4096 Aug 12 19:56 ..
    -rw-r--r--  1 rj rj      17310 Aug 12 19:53 02_3.c
    -rw-r--r--  1 rj rj 1073741824 Aug 12 19:59 test_file

    ==================================================================================
    Sample Input :
    <No Input>

    Sample Output :
    
    rj@RJ:~/assignment03$ ./02_3 test_file
    [+][Server] : Server side socket created sucessfully!!!
    [+][Server] : Binding the server address to the socket sucessfull!!!
    [+][Client] : Client side socket created successfully!!!
    [..][Server] : Server now listening at port 9000

    [+][Client] : Connection established with Server successfully
    [+][Server] : Connection established with Client successfully

    >>>Sending source file from server(Process1) to client(Process2)>>>
    File Succesfully sent!

    <<<Recieving file from client(Process2) to server(Process1)<<<
    File Successfully recieved!

    Time required for both transfers to complete : 23.664669 seconds

    <Authenticating contents of source file and recieved file>
    <Authentication Complete!>
    ***The sent file and received file are identical.***
    IPC using Socket successful.

    Note : Temprorary Process buffer files are created in '/tmp' directory.

    ================== temprorary buffer files created in /tmp directory ====================================
    rj@RJ:~/assignment03$ cd /tmp
    rj@RJ:/tmp$ ls -la
    total 2097180
    drwxrwxrwt  6 root root       4096 Aug 12 20:17 .
    drwxr-xr-x 19 root root       4096 Aug 12 17:12 ..
    -rw-r--r--  1 rj   rj   1073741824 Aug 12 20:18 process1_buffer_file
    -rw-r--r--  1 rj   rj   1073741824 Aug 12 20:17 process2_buffer_file

    ================== Socket details during file transfer =========================================
    Bash command : ss -t -a -p

    rj@RJ:~$ ss -t -a -p
    State     Recv-Q   Send-Q    Local Address:Port    Peer Address:Port  Process
    LISTEN    0        1               0.0.0.0:9000         0.0.0.0:*      users:(("02_3",pid=115,fd=3))
    TIME-WAIT 0        0             127.0.0.1:38510      127.0.0.1:9000
    ESTAB     0        2894254       127.0.0.1:9000       127.0.0.1:57920  users:(("02_3",pid=115,fd=4))
    ESTAB     3542610  0             127.0.0.1:57920      127.0.0.1:9000   users:(("02_3",pid=116,fd=3))
*/

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024      // size of temprorary buffer to hold our file byte by byte
#define LOCALHOST "127.0.0.1" // address of the local host
#define PORT 9000             // port number

#define PROCESS1_BUFFER_FILE "/tmp/process1_buffer_file" // the file received by process 1 is stored temporarily in this buffer
#define PROCESS2_BUFFER_FILE "/tmp/process2_buffer_file" // the file received by process 2 is stored temporarily in this buffer

/* Utitlity function to compare contents of two files */
int file_compare(char *file1, char *file2);

/* Utility functions for file transfer */
long getFileSize(char *filename);
int sendFile(char *source_file, int destination);
int receiveFile(char *destination_file, int source);

/*Utility functions for creating socket connction between server and client */
int createServer();
int acceptConnection(int server_id);
int connectToServer();

/* Server side program*/
void process1(char *source_file);

/* Client side program */
void process2();

/*======================= Driver Function ==============================================================*/
int main(int argc, char *argv[argc + 1])
{

    // CHECK IF FILE PATH IS INPUTTED
    if (argc != 2)
    {
        printf("Input full path of the file to be transferred along with execution command \n");
	printf("Usage : %s <filepath>\n",argv[0]);
        return EXIT_FAILURE;
    }

    /* Source file path of 1GB file to be sent and recieved via sockets */
    char *source_file = argv[1];

    /* Forking to create two processes , in between them files will be transferred */
    pid_t fork_id = fork();

    /* fork() returned negative value , if the program is unable to fork */
    if (fork_id < 0)
    {
        perror("Unable to fork\n");
        return EXIT_FAILURE;
    }

    /* fork() returned 0  , which implies child process */
    else if (fork_id == 0)
    {
        /* Considering child process as  process 2 (Client)*/
        process2();
    }

    /* fork() returned greater than 0  , which implies parent  process */
    else if (fork_id > 0)
    {
        /* Considering parent process as process 1 (Server) */
        process1(source_file);
    }

    return 0;
}

// The file_compare function checks whether the file sent by process1 and the data receive by the process2 are same
int file_compare(char *file1, char *file2)
{
    int file_id1, file_id2; // file ids of the files

    /* Opening first file (input file) in read mode */
    file_id1 = open(file1, O_RDONLY);
    if (file_id1 == -1)
    {
        perror("Error in opening file.\n");
        return -1;
    }

    /* Opening second file (recieved file) in read mode */
    file_id2 = open(file2, O_RDONLY);
    if (file_id2 == -1)
    {
        perror("Error in opening file.\n");
        return -1;
    }

    // buffers to store contents of the file which can be later matched if they are identical
    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];

    int returnValue = 1;

    while (true)
    {
        int len1 = read(file_id1, buffer1, BUFFER_SIZE);
        int len2 = read(file_id2, buffer2, BUFFER_SIZE);
        // if length of the files are -1 then there occurs an error in reading file
        if (len1 == -1 || len2 == -1)
        {
            perror("Error in reading file.\n");
            returnValue = -1;
            break;
        }

        // if the sent and received files are different then their length will differ
        if (len1 != len2)
        {
            returnValue = 0;
            break;
        }

        // if length is 0 , it means we have read the whole file and reached EOF
        if (len1 == 0)
        {
            break;
        }

        // if len1 > 0, we continiue to read.
        for (int i = 0; i < len1; i++)
        {
            if (buffer1[i] != buffer2[i])
            {
                // files are different in their input, hence error has occured while transmission
                returnValue = 0;
                break;
            }
        }

        if (returnValue == 0)
        {
            break;
        }
    }

    // Close files after reading and checking them
    if (close(file_id1) == -1)
    {
        perror("Error in closing file.\n");
        return -1;
    }

    if (close(file_id2) == -1)
    {
        perror("Error in closing file.\n");
        return -1;
    }

    return returnValue;
}

// getting the file size in bytes, this alows us to validate that the entire file has reached the other side
long getFileSize(char *filename)
{
    FILE *file;

    // opening the file
    if ((file = fopen(filename, "r")) == NULL)
    {
        perror("Could not determine file size, fopen error\n");
        return -1;
    }

    // takes the pointer to the end of the file
    if (fseek(file, 0, SEEK_END) == -1)
    {
        perror("Could not determine file size, fseek error\n");
        return -1;
    }

    // gets the size of the file, by calulating the difference between the start of the file and the current position of the pointer in the file
    long size = ftell(file);

    //-1 if is could not be determined
    if (size == -1)
    {
        perror("Could not determine file size, ftell error\n");
        return -1;
    }

    return size;
}

// sending the file via the socket
int sendFile(char *source_file, int destination)
{

    // getting the size of the file
    long fileSize = getFileSize(source_file);

    // error in getting the size of the file
    if (fileSize == -1)
    {
        return -1;
    }

    // buffer/packet to be sent
    char buffer[BUFFER_SIZE];

    // first message sent is the size of the file
    *((long *)buffer) = fileSize;

    // sending the file size to the other side so that the other side can determine of the entire file has been received or not
    if (send(destination, buffer, sizeof(long), 0) < 0)
    {
        perror("Error Sending File!!!\n");
        return -1;
    }

    // opening the file whose content is to be sent
    int file_id = open(source_file, O_RDONLY);

    //-1 if there is an error opening the file
    if (file_id == -1)
    {
        perror("Error Opening File!!!\n");
        return -1;
    }

    int returnValue = 1;

    // infinite loop till the entire file is sent
    while (1)
    {

        // reading from the file into the buffer
        long bufferRead = read(file_id, buffer, BUFFER_SIZE);

        // read() returns -1 if any error has occured
        if (bufferRead < 0)
        {
            perror("Error Reading File!!!\n");
            returnValue = -1;
            break;
        }

        if (bufferRead == 0)
        {
            break; // EOF reached
        }

        // sending the buffer/packet to the other side of the socket, if -1 it has failed to do the job
        if (send(destination, buffer, bufferRead, 0) == -1)
        {
            returnValue = -1;
            break;
        }
    }

    // closing the file
    if (close(file_id) == -1)
    {
        perror("Error closing the file\n");
        return -1;
    }

    // returns 1 is success
    return returnValue;
}

// receiving the file via the socket
int receiveFile(char *destination_file, int source)
{

    // to store the size of the file
    char buffer[BUFFER_SIZE];

    // receives the filesize so as to file_compare that the entire file has been received or not
    if (recv(source, buffer, sizeof(long), 0) < 0)
    {
        perror("Error receiving the file!!!\n");
        return -1;
    }

    // size of the file
    long file_size = *((long *)buffer);

    // opening the destination file, where the contents received via socket will be stored
    int destination_id = open(destination_file, O_WRONLY | O_CREAT, 0666);

    if (destination_id < 0)
    {
        perror("Error opening the file!!!\n");
        return -1;
    }

    long toReceive = file_size;

    int returnValue = 1;

    // infinite loop till the file has been received
    while (toReceive > 0)
    {

        // receiving the contents in form of packets
        int bytesRead = recv(source, buffer, BUFFER_SIZE, 0);

        // is negative is there is an error while recieving the contents of the file
        if (bytesRead < 0)
        {
            perror("Error reading!!!\n");
            returnValue = -1;
            break;
        }

        // end of the file has been reached
        if (bytesRead == 0)
        {
            break;
        }

        // writing into the destination file
        if (write(destination_id, buffer, bytesRead) < 0)
        {
            perror("Error writing\n");
            returnValue = -1;
            break;
        }

        toReceive -= bytesRead;
    }

    // error closing the file
    if (close(destination_id) < 0)
    {
        perror("Error closing\n");
        return -1;
    }

    // return 1 if the file has been recieved successfully
    return returnValue;
}

// creating the server
int createServer()
{

    int server_id;

    // creating the server side interface using TCP/IP protocols
    server_id = socket(AF_INET, SOCK_STREAM, 0);

    // is -1 if it fails to create the server
    if (server_id < 0)
    {
        perror("[Server] : Could not create server side socket!!!!\n");
        return server_id;
    }
    printf("[+][Server] : Server side socket created sucessfully!!!\n");

    // server side address information
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;   // IPv4 family of addresses
    server_address.sin_port = htons(PORT); // adding the port number
    server_address.sin_addr.s_addr = INADDR_ANY;
    bzero(&server_address.sin_zero, 8);

    // binding the server address to the socket created, -1 if fails to bind
    if (bind(server_id, (const struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("[Server] : Could not bind server address to socket.\n");

        if (close(server_id) == -1)
        {
            perror("Error closing !!!\n");
        }

        return -1;
    }

    printf("[+][Server] : Binding the server address to the socket sucessfull!!!\n");

    // listening for the clients
    if (listen(server_id, 1) < 0)
    {
        perror("[Server] : Server listen error\n");
        if (close(server_id) == -1)
        {
            perror("Error closing!!!\n");
        }

        return -1;
    }

    printf("[..][Server] : Server now listening at port %d\n\n", PORT);

    // returning thr server side descripter
    return server_id;
}

// to connect to the server to client
int acceptConnection(int server_id)
{

    int connectionfd;                  // connection socket file descriptor
    struct sockaddr_in client_address; // a sockaddr_in for client
    unsigned int addrlen = sizeof(client_address);

    // accepting the client and connecting to the server
    connectionfd = accept(server_id, (struct sockaddr *)&client_address, &addrlen);

    // is -1 when it fails to accept the client
    if (connectionfd < 0)
    {
        perror("[Server] : Server could not accept connection!!!\n");
        return -1;
    }

    // return server side descriptor
    return connectionfd;
}

// to connect the client to the server
int connectToServer()
{

    // creating the client side of socket interface using TCP/IP protocols
    int client_id = socket(AF_INET, SOCK_STREAM, 0);

    // negative (-1) if fails to create the socket
    if (client_id < 0)
    {
        perror("[Client] : Client side Socket could not be created!!!\n");
        return client_id;
    }
    printf("[+][Client] : Client side socket created successfully!!!\n");

    // address details
    struct sockaddr_in client_address;
    client_address.sin_family = AF_INET;   // IPv4 address family
    client_address.sin_port = htons(PORT); // adding port to the address
    client_address.sin_addr.s_addr = inet_addr(LOCALHOST);
    bzero(&client_address.sin_zero, 8);

    // connecting the server side of the socket, is -1 when it fails to connect
    if (connect(client_id, (struct sockaddr *)&client_address, sizeof(client_address)) < 0)
    {
        perror("[Client] : Client could not connect\n");

        if (close(client_id) == -1)
        {
            perror("close error\n");
        }
        return -1;
    }

    // returning cliert side descriptor
    return client_id;
}

// process1 (server side program)
void process1(char *source_file)
{

    // creating a server socket
    int server_id = createServer();

    // server id is negative if the server socket fails to get created
    if (server_id < 0)
    {
        perror("[Server] : createServer failed\n");
        exit(EXIT_FAILURE);
    }

    // connecting to a client
    int connect_id = acceptConnection(server_id);

    // connect id is negative if the server is not connected the client
    if (connect_id < 0)
    {
        perror("[Server] : acceptConnection failed\n");
        exit(EXIT_FAILURE);
    }

    printf("[+][Server] : Connection established with Client successfully\n");

    // get time to calculate the time
    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);

    // sending to the client
    printf("\n>>>Sending source file from server(Process1) to client(Process2)>>>\n");
    if (sendFile(source_file, connect_id) < 0)
    {
        if (close(connect_id) < 0)
        {
            perror("Close error\n");
        }
        if (close(server_id) < 0)
        {
            perror("Close error\n");
        }

        exit(EXIT_FAILURE);
    }
    printf("File Succesfully sent!\n");
    // receiving the file from the client
    printf("\n<<<Recieving file from client(Process2) to server(Process1)<<<\n");
    if (receiveFile(PROCESS1_BUFFER_FILE, connect_id) < 0)
    {
        if (close(connect_id) < 0)
        {
            perror("Close error\n");
        }
        if (close(server_id) < 0)
        {
            perror("Close error\n");
        }

        exit(EXIT_FAILURE);
    }
    printf("File Successfully recieved!\n");
    // get time close calculate
    gettimeofday(&endTime, NULL);

    // calculate the time taken for the transfer
    double timeValue = (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;

    printf("\nTime required for both transfers to complete : %lf seconds\n", timeValue);

    // file_compare the contents of the file
    printf("\n<Authenticating contents of source file and recieved file>\n");
    int compare = file_compare(source_file, PROCESS1_BUFFER_FILE);
    if (compare > 0)
    {
        printf("<Authentication Complete!>\n***The sent file and received file are identical.***\n");
        printf("IPC using Socket successful.\n");
	printf("\nNote : Temprorary Process buffer files are created in '/tmp' directory.\n");
    }
    else
    {
        perror("\nError : Files are not identical !!!\n");
    }

    // closing the connection to the socket
    if (close(connect_id) < 0)
    {
        perror("Close error\n");
    }

    if (close(server_id) < 0)
    {
        perror("Close error\n");
    }
}

// process2 (client side program)
void process2()
{

    int client_id = connectToServer(); // function to connect to server

    // client_id is -1 for failure in connection
    if (client_id < 0)
    {
        perror("[Client] : connectToServer failed\n");
        exit(EXIT_FAILURE);
    }

    printf("[+][Client] : Connection established with Server successfully\n");

    // receiving file via the socket (from the server)
    if (receiveFile(PROCESS2_BUFFER_FILE, client_id) == -1)
    {
        if (close(client_id) < 0)
        {
            perror("close error\n");
        }
        exit(EXIT_FAILURE);
    }

    // sending file via the socket (from the client)
    if (sendFile(PROCESS2_BUFFER_FILE, client_id) < 0)
    {
        if (close(client_id) == -1)
        {
            perror("close error\n");
        }

        exit(EXIT_FAILURE);
    }
}
