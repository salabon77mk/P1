// Stat explore
// -s, defaults to false, Single char, located in proc/<pid>/stat, 3rd field
// -U, defaults to true,  User time in seconds?, located in stat, 14th field
// -S, defaults to false, System time consumed, in stat, 15th field
// -v, defaults to false, statm, 1st field
// -c, defaults to true, cmdline file, defaults to true
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "procexplore.h"

struct pidStats {
	unsigned int utime;
	unsigned int stime;
	unsigned int size;
	unsigned int pid;
	char state;
	char *cmdline;
};

static void readStatm(long int pid, struct pidStats *pidStat);
static void readCmdline(long int pid, struct pidStats *pidStat);
static void readStat(long int pid, struct pidStats *pidStat);

void getpidinfo(long int *pids, struct pidStats **stats, size_t statStructCount){
	for(int i = 0; i < statStructCount / sizeof(stats) ; i++){
//		readStat(pids[i], stats[i]);
//		readStatm(pids[i], stats[i]);
		readCmdline(pids[i], stats[i]);
	}



}

/*
static void readStat(long int pid, struct pidStats *pidStat){
	char filepath[256];
	char line[2048];
	FILE *fptr;
	
	snprintf(filepath, 256, "/proc/%ld/stat", pid);
	fptr = fopen(filepath, "r");

	if(!fptr){	
		return;
	}	
	
	
	char *lineptr = line;
	char token[2] = " ";
	fgets(line, 2048, fptr);
//	printf("LINE: %s \n NUM: %d \n", line, count);

	int count = 0;
	char* holdRes = strtok(lineptr, token);  
	while(holdRes != NULL){
	
	if(count == 2){
		printf("STATE: %s\n", holdRes); 
	}

	if(count == 13){
		printf("UTIME: %s\n", holdRes);
	}

	if(count ==14){
		printf("STIME: %s\n", holdRes);
	}

	holdRes = strtok(NULL, token);
	count++;
	}

}



static void readStatm(long int pid, struct pidStats *pidStat){
	char filepath[256];
	char line[2048];
	FILE *fptr;
	
	snprintf(filepath, 256, "/proc/%ld/statm", pid);
	fptr = fopen(filepath, "r");

	if(!fptr){	
		return;
	}	
	
	
	
}
*/


static void readCmdline(long int pid, struct pidStats *pidStat){
	char filepath[256];
	char line[256];
	FILE *fptr;
	
	snprintf(filepath, 256, "/proc/%ld/cmdline", pid);
	fptr = fopen(filepath, "r");

	if(!fptr){	
		return;
	}


	char *lineptr = line;
	char token[2] = "\0";
	fgets(line, 2048, fptr);
//	printf("LINE: %s \n NUM: %d \n", line, count);

	int count = 0;
	char* holdRes = strtok(lineptr, token);  
	
	printf("%zu\n", pid);
	while(holdRes != NULL){
	printf("%s\n", holdRes);	
	holdRes = strtok(NULL, token);
	count++;
	}
	printf("\n");

}


int main(void){

	long int someArray[256] = { 0 };
	long int *ptrArr = someArray;
	ptrArr = getPID(someArray, sizeof(someArray));
	size_t arrSize = totalElements(ptrArr, sizeof(someArray));

	struct pidStats **pidArr;
      	pidArr = malloc(sizeof(struct pidStats *) * arrSize);
	
	//malloc each struct
	for(int i = 0; i < arrSize; i++){
		pidArr[i] =  malloc(sizeof(struct pidStats));
	}
	getpidinfo(ptrArr, pidArr, arrSize);

	/*	
	for(int i = 0; i < sizeof(someArray)/sizeof(long int); i++){
		printf("%ld\n", ptrArr[i]);
	}
	*/


	return 0;	
}
