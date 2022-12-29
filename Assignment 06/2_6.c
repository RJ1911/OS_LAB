#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void processorInfo(){
	FILE* fp;
	char buffer[1024];	// Buffer to store cpuinfo data line by line
	size_t bytesRead;	// Number of bytes read in a line
	char* match;		// Used for matching specific fields

	// Required Processor Info:
	char* vendorID;
	char* modelName;
	char* cacheSize;
	char* processorInfo = (char*) malloc(1024*3);

	fp = fopen("/proc/cpuinfo", "rb");
	bytesRead = fread(buffer, 1, sizeof(buffer), fp);
	fclose(fp);

	if(bytesRead==0){
		printf("Error reading the file!\n");
		return;
	}

	// Ending the buffer with null character
	buffer[bytesRead] = '\0';

	match = strstr(buffer, "vendor_id");
	if(match==NULL){
		printf("Vendor ID Not Found!\n");
		return;
	}
	vendorID = (char*)malloc(1024);
	sscanf(match, "vendor_id : %[^\n]", vendorID);

	match = strstr(buffer, "model name");
	if(match==NULL){
		printf("Model Name Not Found!\n");
		return;
	}
	modelName = (char*)malloc(1024);
	sscanf(match, "model name : %[^\n]", modelName);

	match = strstr(buffer, "cache size");
	if(match==NULL){
		printf("Cache Size not Found!\n");
		return;
	}
	cacheSize = (char*) malloc(1024);
	sscanf(match, "cache size : %[^\n]", cacheSize);

	float cache = atof(cacheSize);
	cache /= 1024;

	printf("Processor Info: \n");
	printf("Vendor ID: %s\n", vendorID);
	printf("Model Name: %s\n", modelName);
	printf("Cache Size: %.2fMB\n", cache);
}

void kernelInfo(){
	FILE* fp;
	fp = fopen("/proc/version", "rb");
	
	char* kernelName = (char*) malloc(1024);
	char* release = (char*) malloc(1024);
	char* temp = (char*) malloc(1024);

	fscanf(fp, "%s %s %s", kernelName, temp, release);

	printf("\nKernel Info: \n");
	printf("Kernel Name: %s\n", kernelName);
	printf("Kernel Release: %s\n", release);
}

void memoryInfo(){
	FILE* fp;
	char buffer[1024];	// Buffer to store cpuinfo data line by line
	size_t bytesRead;	// Number of bytes read in a line
	char* match;		// Used for matching specific fields

	// Required Processor Info:
	char* totalMemory;
	char* freeMemory;
	char* availableMemory;
	char* processorInfo = (char*) malloc(1024*3);

	fp = fopen("/proc/meminfo", "rb");
	bytesRead = fread(buffer, 1, sizeof(buffer), fp);
	fclose(fp);

	if(bytesRead==0){
		printf("Error reading the file!\n");
		return;
	}

	// Ending the buffer with null character
	buffer[bytesRead] = '\0';

	match = strstr(buffer, "MemTotal:");
	if(match==NULL){
		printf("Total Memory Info Not Found!\n");
		return;
	}
	totalMemory = (char*)malloc(1024);
	sscanf(match, "MemTotal: %[^\n]", totalMemory);

	match = strstr(buffer, "MemFree:");
	if(match==NULL){
		printf("Free Memory Info Not Found!\n");
		return;
	}
	freeMemory = (char*)malloc(1024);
	sscanf(match, "MemFree: %[^\n]", freeMemory);

	match = strstr(buffer, "MemAvailable:");
	if(match==NULL){
		printf("Available Memory Info not Found!\n");
		return;
	}
	availableMemory = (char*) malloc(1024);
	sscanf(match, "MemAvailable: %[^\n]", availableMemory);

	printf("\nMemory Info: \n");
	printf("Total Memory: %s\n", totalMemory);
	printf("Free Memory: %s\n", freeMemory);
	printf("Available Memory: %s\n", availableMemory);
	
}

void bootTime(){
	FILE* fp;

	fp = fopen("/proc/uptime", "rb");
	long long _uptime;
	fscanf(fp, "%lld", _uptime);
	int hours = _uptime/3600;
	_uptime = _uptime%3600;
	int minutes = _uptime/60;
	_uptime = _uptime%60;
	int seconds = _uptime;

	printf("\nBoot Info:\n");
	printf("Uptime (HH:MM:SS): %2d:%2d:%2d\n", hours, minutes, seconds);
}

int main(){
	processorInfo();
	kernelInfo();
	memoryInfo();
	bootTime();
	return 0;
}
