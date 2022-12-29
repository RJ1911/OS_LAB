/*
	 Group : A1
	 Team Number : 02
	 Date : 25th August , 2022

		 Name               Roll
	 --------------------------------
	 1. Rimil Murmu          039
	 2. Rafson Jani (L)      008
	 3. Rajan Kumar          041
	 4. Pallabi Soren        010
*/

/*
	Assignment : 4 . mmap() and page fault

	Details:
	Objective of this programming assignment is to use mmap() call and observe page-fault using the ‘sar’ command.A big file (about 8GB) should be created using the ‘fallocate’ command.
	This big fileshould be written with a single integer value (say X) at a specific offset (say F). Boththe integer value and the offset should be generated using a random function.
	Please do remember this random function should generate a quantity anywherebetween 0 and 8G.

	The above big file should also be mapped in the virtual address space using mmap()call.
	Once it is mapped, the data should be read from the same specific offset (F).
	Now, if the data read is X`; then verify that X and X` are the same.
	In case ofverification failure, an error message is to be printed.
	Note that, the offset value Fcan be anywhere between 0 and 8G.
	This sequence of writing and reading data to/from a specific offset and alsoverification should be put in a while loop to go forever.
	In another terminal execute the command ‘sar –B 1 1000’ to observe for the pagefault.
	This command should be started before the above program is put underexecution.
	So, one can observe that the page faults are increasing, once the aboveprogram starts executing.
	The output of the program and the ‘sar’ command should be pasted as a comment
	at the beginning of the program file as indicated by the guidelines.

	Input Description:
	<No Input>

	Output Description:
	-> Verfication Result .
	-> Page faults using sar command .


*/

/*
	Creating 8GB file using 'fallocate' command :-

	rj@RJ:~/assignment04$ fallocate -l 8G testfile.txt
	rj@RJ:~/assignment04$ ls -l
	total 8388636
	-rwxr-xr-x 1 rj rj      17368 Aug 25 13:49 02_4
	-rw-r--r-- 1 rj rj       3498 Aug 25 13:31 02_4.c
	-rw-r--r-- 1 rj rj 8589934592 Aug 25 13:55 testfile.txt


	Compilation Command:
	gcc 02_4.c -o 02_4

	Execution Sequence:
	./02_4 testfile.txt

*/

/*

	Sample Input :
	<No input>

	Sample Output :

	rj@RJ:~/assignment04$ ./02_4 testfile.txt
	***Program executes infinite loop!***
	Enter <ctrl+c> or <ctrl+\> to stop execution!
	Written data into file = 7823420738 at offset = 4742780105
	Read data from mapped file = 7823420738 at offset = 4742780105  Verification : Successful

	Written data into file = 6154885768 at offset = 6629384608
	Read data from mapped file = 6154885768 at offset = 6629384608  Verification : Successful

	Written data into file = 7072258404 at offset = 3956255609
	Read data from mapped file = 7072258404 at offset = 3956255609  Verification : Successful

	Written data into file = 2708983181 at offset = 2838462881
	Read data from mapped file = 2708983181 at offset = 2838462881  Verification : Successful

	Written data into file = 643445763 at offset = 2997000806
	Read data from mapped file = 643445763 at offset = 2997000806  Verification : Successful

	Written data into file = 8476494344 at offset = 5761711569
	Read data from mapped file = 8476494344 at offset = 5761711569  Verification : Successful

	Written data into file = 8206388062 at offset = 7257977921
	Read data from mapped file = 8206388062 at offset = 7257977921  Verification : Successful

	Written data into file = 8460608258 at offset = 2115710825
	Read data from mapped file = 8460608258 at offset = 2115710825  Verification : Successful

	Written data into file = 943716189 at offset = 1335112089
	Read data from mapped file = 943716189 at offset = 1335112089  Verification : Successful

	Written data into file = 1318278392 at offset = 6042812718
	Read data from mapped file = 1318278392 at offset = 6042812718  Verification : Successful

	Written data into file = 2246835589 at offset = 4517188381
	Read data from mapped file = 2246835589 at offset = 4517188381  Verification : Successful

	Written data into file = 778014874 at offset = 7925561249
	Read data from mapped file = 778014874 at offset = 7925561249  Verification : Successful

	Written data into file = 2328928690 at offset = 2307843392
	Read data from mapped file = 2328928690 at offset = 2307843392  Verification : Successful

	Written data into file = 8231806252 at offset = 1042367536
	Read data from mapped file = 8231806252 at offset = 1042367536  Verification : Successful

	Written data into file = 1702637010 at offset = 2214768845
	Read data from mapped file = 1702637010 at offset = 2214768845  Verification : Successful

	Written data into file = 7021946825 at offset = 4814832798
	Read data from mapped file = 7021946825 at offset = 4814832798  Verification : Successful
	^C

	=============================================================================================
	Page fault observation using 'sar -B 1 1000' command :-

	rj@RJ:~/assignment04$ sar -B 1 1000
	Linux 5.15.57.1-microsoft-standard-WSL2 (RJ)    08/27/22        _x86_64_        (4 CPU)

	16:57:25     pgpgin/s pgpgout/s   fault/s  majflt/s  pgfree/s pgscank/s pgscand/s pgsteal/s    %vmeff
	16:57:26         0.00      0.00      6.00      0.00     32.00      0.00      0.00      0.00      0.00
	16:57:27         0.00      0.00      0.00      0.00      0.00      0.00      0.00      0.00      0.00
	16:57:28         0.00      0.00      0.00      0.00      1.00      0.00      0.00      0.00      0.00
	16:57:29         0.00      0.00    102.00      0.00     51.00      0.00      0.00      0.00      0.00
	16:57:30         0.00   4344.00      0.00      0.00     98.00      0.00      0.00      0.00      0.00
	16:57:31       236.00      0.00     75.00      0.00    197.00      0.00      0.00      0.00      0.00
	16:57:32       324.00      0.00     89.00      0.00    255.00      0.00      0.00      0.00      0.00
	16:57:33       356.00      0.00     98.00      0.00    284.00      0.00      0.00      0.00      0.00
	16:57:34       320.00      0.00     94.00      0.00    272.00      0.00      0.00      0.00      0.00
	16:57:35       276.00   2904.00     92.00      0.00    304.00      0.00      0.00      0.00      0.00
	16:57:36       364.00      0.00    120.00      0.00    342.00      0.00      0.00      0.00      0.00
	16:57:37       360.00      0.00    116.00      0.00    344.00      0.00      0.00      0.00      0.00
	16:57:38       356.00      0.00    116.00      0.00    317.00      0.00      0.00      0.00      0.00
	16:57:39       340.00      0.00    110.00      0.00    315.00      0.00      0.00      0.00      0.00
	16:57:40       336.00     12.00    113.00      0.00    331.00      0.00      0.00      0.00      0.00
	16:57:41       252.00      0.00     80.00      0.00    233.00      0.00      0.00      0.00      0.00
	16:57:42       332.00      0.00    107.00      0.00    301.00      0.00      0.00      0.00      0.00
	16:57:43       348.00      0.00    124.00      0.00    347.00      0.00      0.00      0.00      0.00
	16:57:44       360.00      0.00    120.00      0.00    372.00      0.00      0.00      0.00      0.00
	16:57:45       328.00     12.00    115.00      0.00    333.00      0.00      0.00      0.00      0.00
	16:57:46       328.00      0.00    125.00      0.00    377.00      0.00      0.00      0.00      0.00
	16:57:47       352.00      0.00    137.00      0.00    374.00      0.00      0.00      0.00      0.00
	16:57:48       324.00      0.00    119.00      0.00    337.00      0.00      0.00      0.00      0.00
	16:57:49       332.00      0.00    155.00      0.00    445.00      0.00      0.00      0.00      0.00
	16:57:50       292.00     12.00    117.00      0.00    343.00      0.00      0.00      0.00      0.00
	16:57:51       292.00      0.00     96.00      0.00    273.00      0.00      0.00      0.00      0.00
	^C

	Average:       261.85    280.15     93.31      0.00    264.54      0.00      0.00      0.00      0.00

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/random.h>
#include <sys/mman.h>
#include <time.h>
#include <string.h>

/* random_number_generator function generates random number between 0 and fileSize*/
long long int random_number_generator(long long int fileSize)
{
	long long int randomNumber;

	/* Using getrandom() function to generate a random number */
	/* if getrandom() throws error ,  it returns -1 as as GRND_NONBLOCK flag is set */
	if (getrandom(&randomNumber, sizeof(long long int), GRND_NONBLOCK) == -1)
	{
		perror("getrandom():");
		exit(1);
	}

	/* if getrandom() genrates negative numbers , making it positive */
	if (randomNumber < 0)
	{
		randomNumber = randomNumber * -1;
	}

	/* Generating numbers in range of 0 to File size .*/
	randomNumber = randomNumber % fileSize;

	return randomNumber;
}

/* Driver function */
int main(int argc, char *argv[argc + 1])
{

	if (argc != 2)
	{
		printf("Please input filepath along with execution command! \nUsage : %s <filepath>\n", argv[0]);
		exit(1);
	}

	char *fileName = argv[1];

	/* Defining a stat structure variable */
	struct stat file_stat;

	if (stat(argv[1], &file_stat) < 0)
	{
		perror("Unable to access file information.");
		exit(1);
	}

	/* Gettting File Size using file_stat variable from stat stucture */
	long long int fileSize = file_stat.st_size;

	/* Warning about infinite loop execution */
	printf("Warning : Program executes infinite loop! \nEnter <ctrl+c> or <ctrl+\\> whenever you want to stop execution!\n");
	sleep(2);

	/* file descriptor */
	int fd;

	/*opening file in read + write mode */
	fd = open(fileName, O_RDWR);

	/* file open error */
	if (fd < 0)
	{
		perror("Unable to open file");
		exit(1);
	}

	/* Mapping file in the virtual address using mmap() */
	char *file_in_memory = mmap(NULL, file_stat.st_size, PROT_READ, MAP_SHARED, fd, 0);

	/* In case mapping fails MAP_FAILED is returned */
	if (file_in_memory == MAP_FAILED)
	{
		perror("Mapping Error : ");
		exit(1);
	}

	/* infinite while loop */
	while (1)
	{

		/* generating random number for offset */
		long long int offset = random_number_generator(fileSize);

		/*generating random data to be written at specific offset */
		long long int data_at_offset = random_number_generator(fileSize);

		/*setting cursor to offset position using lseek function */
		long long int set_offset = lseek(fd, offset, SEEK_SET);

		/* if lseek() throws error it returns -1 */
		if (set_offset < 0)
		{
			perror("lseek:");
			close(fd);
			exit(1);
		}

		char str[20];

		/*Converting long long int data to string */
		sprintf(str, "%lld", data_at_offset);

		/* In case offset + length of data to be written causes overflow condition */
		if ((fileSize - offset) < (strlen(str) + 1))
		{
			offset = offset - (strlen(str) + 1);
		}

		/*Writing random generated data at specific offset */
		set_offset = write(fd, str, sizeof(str));

		/* writing in file error */
		if (set_offset < 0)
		{
			perror("Unable to write in file");
			close(fd);
			exit(1);
		}
		else
		{
			printf("Written data into file = %lld at offset = %lld ", data_at_offset, offset);
		}

		/*verifying data written in file earlier and value read from file now */
		printf("\nRead data from mapped file = ");
		for (int i = 0; str[i] != '\0'; i++)
		{
			if (file_in_memory[offset + i] == str[i])
			{
				printf("%c", file_in_memory[offset + i]);
			}
			else
			{
				perror(" Verfication Failure \n");
			}
		}
		printf(" at offset = %lld ", offset);
		printf(" Verification : Successful \n\n");
	}

	/* closing file */
	close(fd);

	/* Unmapping file */
	int unmaping_file = munmap(file_in_memory, file_stat.st_size);
	if (unmaping_file < 0)
	{
		perror("Unmapping error : ");
		exit(1);
	}

	return 0;
}
