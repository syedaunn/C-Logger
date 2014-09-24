C-Logger
========

Simple file logger in C for debugging large C programs

usage:
-Add header file to your c code i.e. #include "logger.h"

call the following function to write log to file.

filename can be given by macro: __FILE__
line number can be given by macro: __LINE__

    //void log_print(int debug_level,int rank,char* filename, int line, char *fmt,...);  //signature
    e.g: log_print(DEBUG,0,__FILE__,__LINE__,"I have an error code %d",code);

Debug levels can be one of the following:
    INFO, DEBUG, ERROR, WARNING
    
Rank states the file number you want to write on a specific host. useful when debugging multi-thread code or working with mpi processes.


