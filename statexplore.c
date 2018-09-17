// Stat explore
// -s, defaults to false, Single char, located in proc/<pid>/stat, 3rd field
// -U, defaults to true,  User time in seconds?, located in stat, 14th field
// -S, defaults to false, System time consumed, in stat, 15th field
// -v, defaults to false, statm, 1st field
// -c, defaults to true, cmdline file, defaults to true
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "procexplore.h"

struct pidStats {
	unsigned int utime;
	unsigned int stime;
	unsigned int size;
	unsigned int pid;
	char state;
	char *cmdline;
};

static void readCmdline(long int pid, struct pidStats *pidStat);
static void readStat(long int pid, struct pidStats *pidStat);
static void readStatm(long int pid, struct pidStats *pidStat);

void getpidinfo(long int *pids, struct pidStats **stats, size_t pidSize, size_t statStructCount){
	for(int i = 0; i < statStructCount / sizeof(stats) ; i++){
		readStat(pids[i], stats[i]);
//		readStatm(pids[i], stats[i]);
//		readCmdline(pids[i], stats[i]);
	}



}

static void readStat(long int pid, struct pidStats *pidStat){
	char filepath[256];
	char line[100];
	FILE *fptr;
	
	snprintf(filepath, 256, "/proc/%ld/stat", pid);
	fptr = fopen(filepath, "r");

	if(!fptr){	
		return;
	}	

	while(fgets(line, 100, fptr)){
		
	}

}
/**
static void readStatm(long int pid, struct pidStats *pidStat){
	char filepath[256];
	char line[2048];
	FILE *fptr;
	
	snprintf(filepath, 256, "/proc/%ld/statm", pid);
	fptr = fopen(filepath, "r");

	if(!fptr){	
		return;
	}

	

	
	while(fgets(line, 2048, fptr)){
		char *lineConts = line;
		sscanf(lineCo
	}
	
}

static void readCmdline(long int pid, struct pidStats *pidStat){
	char filepath[256];
	char line[256];
	FILE *fptr;
	
	snprintf(filepath, 256, "/proc/%ld/cmdline", pid);
	fptr = fopen(filepath, "r");

	if(!fptr){	
		return;
	}

	while(fgets(line, 256, fptr)){
		//Test this one out, not sure of behavior
		pidStat->cmdline = strtok(line, "\0");		
	}

}
*/

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

	/*	
	for(int i = 0; i < sizeof(someArray)/sizeof(long int); i++){
		printf("%ld\n", ptrArr[i]);
	}
	*/


	return 0;	
}
