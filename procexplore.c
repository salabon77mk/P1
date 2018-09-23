#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include "procexplore.h"

#ifndef PATH_LEN
#define PATH_LEN 1048
#endif

#ifndef LINE_LEN
#define LINE_LEN 256
#endif


static int isUserPID(long processNum);

/* Fill out an array with all pids belonging to the user
 *
 * 
 * *arr: pointer to an array
 * size: used to keep track of array indices
 */

void getPID(long int * arr, size_t size){
	struct dirent *dp;
	size_t arrElement = 0;
	long int *ptrArr = arr;

	DIR *dir = opendir("/proc");

	while((dp=readdir(dir)) != NULL){

		if(!isdigit(*dp->d_name)){
			continue;	}

		long int pidNum = strtol(dp->d_name, NULL, 10);
		int i = isUserPID(pidNum);

		if( i  == 1 && arrElement < size / (sizeof(long int) )){
			ptrArr[arrElement] = pidNum;
			arrElement++;		
		}
		
	}
	arr = ptrArr;
	closedir(dir);
}

/* Only called if -p flag is present
 * Returns the PID if it exists
 * Otherwise returns -1 if not found
 *
 */
long int getSinglePID(long int *arr){
	struct dirent *dp;
	DIR *dir = opendir("/proc");

	while((dp=readdir(dir)) != NULL){
		long int currPID = -1;

		if(!isdigit(*dp->d_name)){
			continue;
		}
	
		sscanf(&(*dp->d_name), "%ld", &currPID);
		//It's an array here because we pass arrays in through main
		if(currPID == arr[0]){
			//Return PID so it'll work with other funcs
			closedir(dir);
			return currPID;
		}
	
	}
	//PID NOT FOUNiD
	closedir(dir);
	return -1;

}

/* Helper function for getPID
 * Verifies that the current pid belongs to the current user
 * Will return 1 if pid is the users
 *             0 if pid is not users
 *            -1 if the status is empty or doesn't exist
 */
static int isUserPID(long processNum){
	char filepath[PATH_LEN];
	char line[LINE_LEN];
	FILE *fptr;
	
	snprintf(filepath, PATH_LEN, "/proc/%ld/status", processNum);

	fptr = fopen(filepath, "r");

	if(!fptr){	
		return -1;
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
				fclose(fptr);
				return 1;
			}

			else{
				fclose(fptr);
				return 0;
			}
		}
	}
	fclose(fptr);
	return -1;	
}

/* Counts up the number of elements within the array
 *
 *
 */
size_t totalElements(long int *arr, size_t arrSize){
	size_t count = 0;

	for(size_t i = 0; i < arrSize; i++){	
		if(arr[i] == 0){
			break;
		}		
		count++;
	}
	return count;
}

