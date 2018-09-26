# P1
---------------------------------------------------------------
COMPILE PROGRAM:
Type 'make' and then run ./537ps with desired options
---------------------------------------------------------------

We created a module that can display info about processes. The user can use the -p option to get info on the PID of their choosing. If no -p is provided
then ALL PIDs will be displayed.

The flow of the program has been split across some files.

cmdparse.c - Parses the arguments and creates flags that will be used later when printing out info
procexplore.c - In general, this will scan through the /proc directory. If no PID is provided, it will retrieve all PIDs belonging to the user, otherwise
		it finds the PID specified by the user
statexplore.c - There is a separate function here for each file that will be read in /proc/<PID>/ namely stat, statm, and cmdline. The results of reading these
		files will fill out the fields of struct pidStats which contains fields for pid, stime, utime, state, cmd
main.c - Driver file that will print out the results. There is a helper function that makes main look cleaner and will allow further customization
	should we ever desire to read more fields

Gen flow:
Parse commands -> Main will call one of two functions in procexplore.c depending if PID was provided as an argument -> procexplore will provide desired PID(s) -> statexplore will
fill out a struct with info from stat, statm, cmdline files -> Main will now print the contents found within the structs
