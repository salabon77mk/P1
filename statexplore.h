/* Authors:
 * Mykola Kusyy
 * Garrett McLaughlin
 */
// Stat headers
#include <stdlib.h>
struct pidStats {
	unsigned long utime;
	unsigned long stime;
	unsigned long size;
	int pid;
	char state;
	char *cmdline;
};


void getpidinfo(long int *pids, struct pidStats **stats, size_t statStructCount);
