#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

################################################################################
#
# Variable declaration and initilization section.
# Each of the following flag variables are marked as extern in cmdparse.h
#
# flag_p : NULL if unspecified,                        POS INT if specified
# flag_s : 0 if state should be hidden,                1 if it should be shown
# flag_U : 0 if user time should be hidden,            1 if it should be shown
# flag_S : 0 if system time should be hidden,          1 if it should be shown
# flag_v : 0 if virtual memory should be hidden,       1 if it should be shown
# flag_c : 0 if command line code should be hidden,    1 if it should be shown
#
# All flags have defaults which are specified below, except for flag_p.
#
################################################################################

int flag_p;
int flag_s = 0;
int flag_U = 1;
int flag_S = 0;
int flag_v = 0;
int flag_c = 1;


/**
* This function serves as a module for getopt. It takes two arguments, argc
* and *argv[], which are passed to getopt.
*
* argc : argument count
* argv : argument vector
*
* return : 0 if success, 1 if failure
*/
int parse_cmd( int argc, char *argv[] ) {
    int opt;   // Option to be parsed
    char prev; // Previously parsed option
    while((opt = getopt(argc, argv, "p:sUSvc")) != -1) {
        opterr = 0; // Turn off getopt error handling
        switch (opt) {
            case 'p':
                flag_p = atoi(optarg);
                prev = 'p';
                break;
            case 's':
                flag_s = 1;
                prev = 's';
                break;
            case 'U':
                prev = 'U';
                break;
            case 'S':
                flag_S = 1;
                prev = 'S';
                break;
            case 'v':
                flag_v = 1;
                prev = 'v';
                break;
            case 'c':
                prev = 'c';
                break;
            case ':':
                printf("Option '-%c' requires an argument\n", optopt);
                break;
            case '?':
                if (optopt == '-') {
                    switch (prev) {
                        case 'U':
                            flag_U = 0;
                            break;
                        case 'c':
                            flag_c = 0;
                            break;
                        default:
                            break;
                    }
                } else {
                    printf("Invalid option %c\n", optopt);
                    return(EXIT_FAILURE);
                }
            default:
                printf("The option '-%c' is invalid.\n", optopt);
                printf("Please use this format: -p [PID] -s -U -S -v -c");
                return(EXIT_FAILURE);
                break;
        }
    }
    return(EXIT_SUCCESS);
}
