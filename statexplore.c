// Stat explore
// -s, defaults to false, Single char, located in proc/<pid>/stat, 3rd field
// -U, defaults to true,  User time in seconds?, located in stat, 14th field
// -S, defaults to false, System time consumed, in stat, 15th field
// -v, defaults to false, statm, 1st field
// -c, defaults to true, cmdline file, defaults to true


struct statFields {
	char state;
	unsigned int utime;
	unsigned int stime;
	unsigned int size;
	char *cmd;
};
