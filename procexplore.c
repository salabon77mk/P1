// Proc Explore
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include "procexplore.h"

//First function should return only the PID specified
#ifndef PATH_LEN
#define PATH_LEN 1048
#endif

#ifndef LINE_LEN
#define LINE_LEN 256
#endif



static int isUserPID(long processNum);


long int * getPID(long int * arr, size_t size){
	struct dirent *dp;
	int arrElement = 0;
	long int *ptrArr = arr;

	DIR *dir = opendir("/proc");

	while((dp=readdir(dir)) != NULL){

		if(!isdigit(*dp->d_name)){
			continue;	}

		long int pidNum = strtol(dp->d_name, NULL, 10);
		int i = isUserPID(pidNum);
//		printf("PIDNUM %ld\n", pidNum);
//		printf("AM I UNDER USER %d\n", i);		
		if( i  == 1 && arrElement < size / (sizeof(long int) )){
			ptrArr[arrElement] = pidNum;
			arrElement++;		
		}
		
	}
	arr = ptrArr;
	return arr;	

}

// TEST THIS ONE
long int getSinglePID(long int PID){
	struct dirent *dp;
	DIR *dir = opendir("/proc");

	while((dp=readdir(dir)) != NULL){
		long int currPID = -1;

		if(!isdigit(*dp->d_name)){
			continue;
		}
	
		sscanf(&(*dp->d_name), "%ld", &currPID);

		if(currPID == PID){
			//Return PID so it'll work with other funcs
			return PID;
		}
	
	}
	//PID NOT FOUND
	return -1;

}



static int isUserPID(long processNum){
	char filepath[PATH_LEN];
	char line[LINE_LEN];
	FILE *fptr;
	
	snprintf(filepath, PATH_LEN, "/proc/%ld/status", processNum);

	fptr = fopen(filepath, "r");

	if(!fptr){	
		return 0;
	}	


	while(fgets(line, LINE_LEN, fptr)){
		
		if(strncmp(line, "Uid:", 4) == 0){
			long int uid  = getuid();
			int uidLen = 0;
			//get digit count
			while(uid != 0){
				uid /= 10;
				uidLen++;
			}	
			uid = getuid();


			char minUID[4]; //we only need the first four dig to see if its a UUSER
			strncpy(minUID, line + 5, uidLen);
			long int uidInFile = strtol(minUID, NULL, 10);
				
		
			if(uidInFile == uid){
//				printf("Line: %s", line);
//				printf("String: %s\n", minUID);
//				printf("UID: %ld\n\n", UID);
				fclose(fptr);
				return 1;
			}

			else{
				fclose(fptr);
				return 0;
			}
		}
		
		
	
	}
	
}

size_t totalElements(long int *arr, size_t arrSize){
	size_t count = 0;
	for(int i = 0; i < arrSize/sizeof(long int); i++){
		if(arr[i] == 0){
			break;
		}		
		count++;
	}
	return count;

}

