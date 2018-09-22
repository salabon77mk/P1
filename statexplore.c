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
#include "statexplore.h"

#ifndef BUFF_SIZE
#define BUFF_SIZE 2048
#endif

#ifndef DEFAULT_ARR_SIZE 
#define DEFAULT_ARR_SIZE 256
#endif


void getpidinfo(long int *pids, struct pidStats **stats, size_t statStructCount){
	for(int i = 0; i < statStructCount ; i++){
		char pidChar[11]; //PID can go up to 2 something billion
		snprintf(pidChar, 11, "%lu", pids[i]);

		sscanf(pidChar, "%d", &(stats[i]->pid));
		readStat(pids[i], stats[i]);
		readStatm(pids[i], stats[i]);
		readCmdline(pids[i], stats[i]);
	}

}


static void readStat(long int pid, struct pidStats *pidStat){
	char filepath[DEFAULT_ARR_SIZE];
	char line[BUFF_SIZE];
	FILE *fptr;
	
	snprintf(filepath, DEFAULT_ARR_SIZE, "/proc/%ld/stat", pid);
	fptr = fopen(filepath, "r");

	if(!fptr){	
		return;
	}	
	
	
	char *lineptr = line;
	char token[2] = " ";
	fgets(line, BUFF_SIZE, fptr);
//	printf("LINE: %s \n NUM: %d \n", line, count);

	int count = 0;
	char* holdRes = strtok(lineptr, token);  
	while(holdRes != NULL){
	
	if(count == 2){
//		printf("STATE: %s\n", holdRes);
	       sscanf(holdRes, "%c", &(pidStat->state));	
	}

	if(count == 13){
//		printf("UTIME: %s\n", holdRes);
	       sscanf(holdRes, "%lu", &(pidStat->utime));	
	}

	if(count ==14){
	}

	holdRes = strtok(NULL, token);
	count++;
	}

}



static void readStatm(long int pid, struct pidStats *pidStat){
	char filepath[DEFAULT_ARR_SIZE];
	char line[BUFF_SIZE];
	FILE *fptr;
	
	snprintf(filepath, DEFAULT_ARR_SIZE, "/proc/%ld/statm", pid);
	fptr = fopen(filepath, "r");

	if(!fptr){	
		return;
	}	
	char *lineptr = line;
	char token[2] = " ";
	fgets(line, BUFF_SIZE, fptr);

	char* holdRes = strtok(lineptr, token);  
	sscanf(holdRes, "%lu", &(pidStat->size));
	
	
	
}



static void readCmdline(long int pid, struct pidStats *pidStat){
	char filepath[DEFAULT_ARR_SIZE];
	char line[BUFF_SIZE];
	FILE *fptr;
	
	snprintf(filepath, BUFF_SIZE, "/proc/%ld/cmdline", pid);
	fptr = fopen(filepath, "r");

	if(!fptr){	
		fclose(fptr);
		return;
	}

	char* fileCont = (char *) calloc(BUFF_SIZE, sizeof(char));
	size_t fileSize = fread(fileCont, sizeof(char), BUFF_SIZE, fptr);
	
	if(fileSize > 0){
		if(fileCont[fileSize-1] == '\n'){
			fileCont[fileSize-1] = '\0';
		}

		pidStat->cmdline = fileCont;
	
	}
	else{
		pidStat->cmdline = "";
	}

	fclose(fptr);

}

