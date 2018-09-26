/* Authors:
 * Mykola Kusyy
 * Garrett McLaughlin
 */
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

static void readStatm(long int pid, struct pidStats *pidStat);
static void readCmdline(long int pid, struct pidStats *pidStat);
static void readStat(long int pid, struct pidStats *pidStat);


// Fills out the pidStats struct array by calling relevant helper functions

void getpidinfo(long int *pids, struct pidStats **stats, size_t statStructCount){
	for(size_t i = 0; i < statStructCount ; i++){
		char pidChar[11]; //PID can go up to 2 something billion so we need 10 to represent billion and 1 for NULL
		snprintf(pidChar, 11, "%lu", pids[i]);

		sscanf(pidChar, "%d", &(stats[i]->pid));
		readStat(pids[i], stats[i]);
		readStatm(pids[i], stats[i]);
		readCmdline(pids[i], stats[i]);
	}

}

// Helper function that reads the stat file
static void readStat(long int pid, struct pidStats *pidStat){
	char filepath[DEFAULT_ARR_SIZE];
	char line[BUFF_SIZE];
	FILE *fptr;
	
	snprintf(filepath, DEFAULT_ARR_SIZE, "/proc/%ld/stat", pid);
	fptr = fopen(filepath, "r");

	if(!fptr){
		fclose(fptr);	
		return;
	}	
	
	
	char *lineptr = line;
	char token[2] = " ";
	fgets(line, BUFF_SIZE, fptr);

	int count = 0; //keep track of which string we're looking at
	char* holdRes = strtok(lineptr, token);  
	while(holdRes != NULL){
	
	if(count == 2){
	       sscanf(holdRes, "%c", &(pidStat->state));	
	}

	if(count == 13){
	       sscanf(holdRes, "%lu", &(pidStat->utime));	
	}

	if(count ==14){
	       sscanf(holdRes, "%lu", &(pidStat->stime));	
	}

	holdRes = strtok(NULL, token); //get next token
	count++;
	}
	fclose(fptr);	

}

// Helper function that reads the statm file
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
	
	fclose(fptr);	
	
}

// Helper function that reads the cmdline file
static void readCmdline(long int pid, struct pidStats *pidStat){
	char filepath[DEFAULT_ARR_SIZE];
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
			fileCont[fileSize-1] = '\0'; //ensure it the string ends with null
		}
		pidStat->cmdline = fileCont;
	}

	else{
		pidStat->cmdline = ""; //empty file
	}

	fclose(fptr);

}

