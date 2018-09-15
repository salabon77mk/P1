// Proc Explore


#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>


//First function should return only the PID specified


static int isUserPID(long processNum);


long int * getPID(){
	struct dirent *dp;
	long int userPIDs[1024];
	long int *PIDs = userPIDs;

	DIR *dir = opendir("/proc");

	while((dp=readdir(dir)) != NULL){
		int count = 0;
		if(!isdigit(*dp->d_name)){
			continue;	}

		long int pidNum = strtol(dp->d_name, NULL, 10);
		int i = isUserPID(pidNum);

		
		if( i  == 1){
			userPIDs[i] = pidNum;		
		  	count++;
		}
		

	}
	return PIDs;	

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
			
			char minUID[4]; //we only need the first four dig to see if its a UUSER
			strncpy(minUID, line + 5, 4);
			long int UID = strtol(minUID, NULL, 10);
			/*
			printf("Line: %s", line);
			printf("String: %s\n", minUID);
			printf("UID: %ld\n\n", UID);
			*/
			if(UID >= 1000){
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


int main(){
	long int * gimme = getPID();
	


	return 0;	
}
