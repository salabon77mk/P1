#include "cmdparse.h"
#include "statexplore.h"
#include "procexplore.h"
#include <stdio.h>

#ifndef DEF_ARR_SIZE
#define DEF_ARR_SIZE 1024
#endif

void printProc(struct pidStats **stats, size_t statStructCount);

int main( int argc, char *argv[] ){
	parse_cmd(argc, argv);

	long pidArr[DEF_ARR_SIZE];
	long *ptrPIDS = pidArr;
	size_t arrSize = 0;
	struct pidStats **statsArr;


        if(!pidArr){
		printf("Out of memory");
		return EXIT_FAILURE;
	}	

	//single PID
	if(flag_p){
		pidArr[0] = flag_p;
		pidArr[0] = getSinglePID(ptrPIDS);

		if(pidArr[0] == -1){
			printf("PID not found");
			return 0;
		}
		arrSize = 1; // Single element
		statsArr = malloc(sizeof(struct pidStats *));
		statsArr[0] = malloc(sizeof(struct pidStats));
		getpidinfo(ptrPIDS, statsArr, arrSize);
		printProc(statsArr, arrSize);			

	}

	//get all userPIDs
	else{
		getPID(ptrPIDS, DEF_ARR_SIZE);
		arrSize = totalElements(ptrPIDS, DEF_ARR_SIZE);
		statsArr = malloc(sizeof(struct pidStats *) * arrSize);
	
		for(int i = 0; i < arrSize; i++){
			statsArr[i] =  malloc(sizeof(struct pidStats));
		}
		getpidinfo(ptrPIDS, statsArr, arrSize);
		printProc(statsArr, arrSize);
			
	}

	return EXIT_SUCCESS;	    
}


void printProc(struct pidStats **stats, size_t statStructCount){
	
	for (int i = 0; i < statStructCount; i++) {
		// pid:
		printf("%d: ", stats[i]->pid);

		if (flag_s) {
			printf("%c ", stats[i]->state);
		}
		if (flag_U) {
			printf("utime=%lu ", stats[i]->utime); 
		}
		if (flag_S) {
			printf("stime=%lu ", stats[i]->stime);
		}
		if (flag_v) {
			printf("vmemory=%lu ", stats[i]->size);
		}
		if (flag_c) {
			printf("[%s]", stats[i]->cmdline);
		}
		printf("\n");
	}

}

