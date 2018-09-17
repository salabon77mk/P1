// Proc Explore

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>


//First function should return only the PID specified


static int isUserPID(long processNum);


long int * getPID(long int * arr, size_t size){
	struct dirent *dp;
	int arrElement = 0;
	long int *ptrArr = arr;

	DIR *dir = opendir("/proc");

	while((dp=readdir(dir)) != NULL){
		int count = 0;
		if(!isdigit(*dp->d_name)){
			continue;	}

		long int pidNum = strtol(dp->d_name, NULL, 10);
		int i = isUserPID(pidNum);
//		printf("PIDNUM %ld\n", pidNum);
//		printf("AM I UNDER USER %d\n", i);		
		if( i  == 1 && arrElement < size/(sizeof(long int) )){
			ptrArr[arrElement] = pidNum;
			arrElement++;		
		}
		
	}
	arr = ptrArr;
	return arr;	

}

static int isUserPID(long processNum){
	char filepath[256];
	char line[100];
	FILE *fptr;
	
	snprintf(filepath, 256, "/proc/%ld/status", processNum);

	fptr = fopen(filepath, "r");

	if(!fptr){	
		return 0;
	}	


	while(fgets(line, 100, fptr)){
		
		if(strncmp(line, "Uid:", 4) == 0){
			long int uid  = getuid();
			int uidLen = 0;
			//get digit count
			while(uid != 0){
				uid /= 10;
				uidLen++;
			}	



			char minUID[4]; //we only need the first four dig to see if its a UUSER
			strncpy(minUID, line + 5, uidLen);
			long int UID = strtol(minUID, NULL, 10);
				
		
			if(UID >= 1000){
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



