// Stat explore
// -s, defaults to false, Single char, located in proc/<pid>/stat, 3rd field
// -U, defaults to true,  User time in seconds?, located in stat, 14th field
// -S, defaults to false, System time consumed, in stat, 15th field
// -v, defaults to false, statm, 1st field
// -c, defaults to true, cmdline file, defaults to true
#include <stdio.h>
#include <stdlib.h>


struct pidStats {
	unsigned int utime;
	unsigned int stime;
	unsigned int size;
	unsigned int pid;
	char state;
	char *cmd;
};

static void readStat(long int pids, struct pidStats *pid);
static void readStatm(long int pids, struct pidStats *pid);

void getpidinfo(long int *pids, struct pidStats **stats, size_t pidSize, size_t statStructCount){
	for(int i = 0; i < statStructCount / sizeof(stats) ; i++){
		readStat(pids[i], stats[i]);
		readStatm(pids[i], stats[i]);
	}



}

static void readStat(long int pids, struct pidStats *pid){
	

}

static void readStatm(long int pids, struct pidStats *pid){

}

int main(void){
/*
	long int someArray[256] = { 0 };
	long int *ptrArr = someArray;
	ptrArr = getPID(someArray, sizeof(someArray));
	
	for(int i = 0; i < sizeof(someArray)/sizeof(long int); i++){
		printf("%ld\n", ptrArr[i]);
	}
	
*/
	return 0;	
}
