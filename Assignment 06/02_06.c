/*
	 Group : A1
	 Team Number : 02
	 Date : 5th September , 2022
		 Name               Roll
	 --------------------------------
	 1. Rimil Murmu          039
	 2. Rafson Jani (L)      008
	 3. Rajan Kumar          041
	 4. Pallabi Soren        010
*/

/*
	Assignment : 6. Observing the OS through the /proc file system
	Details:

	The OS is a program that uses various data structures. Like all programs in
	execution, you can determine the performance and other behaviour of the OS by
	inspecting its state - the values stored in its data structures. In this part of the
	assignment, we study some aspects of the organization and behaviour of a Linux
	system by observing values of kernel data structures exposed through the /proc
	virtual file system.

	The /proc virtual file system:
	Linux uses the /proc file system to collect information from kernel data structures.
	The /proc implementation provided with Linux can read many different kernel data
	structures. If you cd to /proc on a Linux machine, you will see a number of files and
	directories at that location. Files in this directory subtree each correspond to some
	kernel data structure. The subdirectories with numeric names contain virtual files
	with information about the process whose process ID is the same as the directory
	name. Files in /proc can be read like ordinary ASCII files. You can open each file
	and read it using library routines such as fgets() or fscanf(). The proc (5) manual
	page explains the virtual files and their content available through the /proc file
	system.

	Requirements in detail:
	You are supposed to write a C program which should print the following values on
	terminal
		● Processor Informations (Vendor ID, Model Name and Cache Size in MB)
		● Kernel Name, Kernel Release and Operating System Name.
		● The amount of memory configured into this computer and Free Memory
		● Amount of time since the system was last booted (In Hours, Minutes,Seconds)

	Input Description:
	<No Input>
	Output Description:
	-> Processor Informations (Vendor ID, Model Name and Cache Size in MB)
	-> Kernel Name, Kernel Release and Operating System Name.
	-> The amount of memory configured into this computer and Free Memory 
	-> Amount of time since the system was last booted (In Hours, Minutes, Seconds)
*/

/*
	Compilation Command:
	gcc 02_6.c -o 02_6

	Execution Sequence:
	./02_6

*/

/*
	Sample Input :
	<No input>

	Sample Output :

	Processor Info:
	Vendor ID: GenuineIntel
	Model Name: Intel(R) Core(TM) i3-1005G1 CPU @ 1.20GHz
	Cache Size: 4.00MB

	Kernel Info:
	Kernel Name: Linux
	Kernel Release: 5.15.57.1-microsoft-standard-WSL2

	Memory Info:
	Total Memory: 3894244 kB
	Free Memory: 3466492 kB
	Available Memory: 3424524 kB

	Boot Info:
	Uptime (HH:MM:SS):  0:10:37

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void processorInfo()
{
	FILE *fp;
	char buffer[1024]; // Buffer to store cpuinfo data line by line
	size_t bytesRead;  // Number of bytes read in a line
	char *match;	   // Used for matching specific fields

	// Required Processor Info:
	char *vendorID;
	char *modelName;
	char *cacheSize;
	char *processorInfo = (char *)malloc(1024 * 3);

	fp = fopen("/proc/cpuinfo", "rb");
	bytesRead = fread(buffer, 1, sizeof(buffer), fp);
	fclose(fp);

	if (bytesRead == 0)
	{
		printf("Error reading the file!\n");
		return;
	}

	// Ending the buffer with null character
	buffer[bytesRead] = '\0';

	match = strstr(buffer, "vendor_id");
	if (match == NULL)
	{
		printf("Vendor ID Not Found!\n");
		return;
	}
	vendorID = (char *)malloc(1024);
	sscanf(match, "vendor_id : %[^\n]", vendorID);

	match = strstr(buffer, "model name");
	if (match == NULL)
	{
		printf("Model Name Not Found!\n");
		return;
	}
	modelName = (char *)malloc(1024);
	sscanf(match, "model name : %[^\n]", modelName);

	match = strstr(buffer, "cache size");
	if (match == NULL)
	{
		printf("Cache Size not Found!\n");
		return;
	}
	cacheSize = (char *)malloc(1024);
	sscanf(match, "cache size : %[^\n]", cacheSize);

	float cache = atof(cacheSize);
	cache /= 1024;

	printf("Processor Info: \n");
	printf("Vendor ID: %s\n", vendorID);
	printf("Model Name: %s\n", modelName);
	printf("Cache Size: %.2fMB\n", cache);
}

void kernelInfo()
{
	FILE *fp;
	fp = fopen("/proc/version", "rb");

	char *kernelName = (char *)malloc(1024);
	char *release = (char *)malloc(1024);
	char *temp = (char *)malloc(1024);

	fscanf(fp, "%s %s %s", kernelName, temp, release);

	printf("\nKernel Info: \n");
	printf("Kernel Name: %s\n", kernelName);
	printf("Kernel Release: %s\n", release);
}

void memoryInfo()
{
	FILE *fp;
	char buffer[1024]; // Buffer to store cpuinfo data line by line
	size_t bytesRead;  // Number of bytes read in a line
	char *match;	   // Used for matching specific fields

	// Required Processor Info:
	char *totalMemory;
	char *freeMemory;
	char *availableMemory;
	char *processorInfo = (char *)malloc(1024 * 3);

	fp = fopen("/proc/meminfo", "rb");
	bytesRead = fread(buffer, 1, sizeof(buffer), fp);
	fclose(fp);

	if (bytesRead == 0)
	{
		printf("Error reading the file!\n");
		return;
	}

	// Ending the buffer with null character
	buffer[bytesRead] = '\0';

	match = strstr(buffer, "MemTotal:");
	if (match == NULL)
	{
		printf("Total Memory Info Not Found!\n");
		return;
	}
	totalMemory = (char *)malloc(1024);
	sscanf(match, "MemTotal: %[^\n]", totalMemory);

	match = strstr(buffer, "MemFree:");
	if (match == NULL)
	{
		printf("Free Memory Info Not Found!\n");
		return;
	}
	freeMemory = (char *)malloc(1024);
	sscanf(match, "MemFree: %[^\n]", freeMemory);

	match = strstr(buffer, "MemAvailable:");
	if (match == NULL)
	{
		printf("Available Memory Info not Found!\n");
		return;
	}
	availableMemory = (char *)malloc(1024);
	sscanf(match, "MemAvailable: %[^\n]", availableMemory);

	printf("\nMemory Info: \n");
	printf("Total Memory: %s\n", totalMemory);
	printf("Free Memory: %s\n", freeMemory);
	printf("Available Memory: %s\n", availableMemory);
}

void bootTime()
{
	FILE *fp;

	fp = fopen("/proc/uptime", "rb");
	long long _uptime;
	fscanf(fp, "%lld", _uptime);
	int hours = _uptime / 3600;
	_uptime = _uptime % 3600;
	int minutes = _uptime / 60;
	_uptime = _uptime % 60;
	int seconds = _uptime;

	printf("\nBoot Info:\n");
	printf("Uptime (HH:MM:SS): %2d:%2d:%2d\n", hours, minutes, seconds);
}

int main()
{
	processorInfo();
	kernelInfo();
	memoryInfo();
	bootTime();
	return 0;
}
