//#define LOG_PRINT(...) log_print(__FILE__, __LINE__, __VA_ARGS__ )

#ifndef logger_h

#define logger_h

enum log_level{
	INFO=0,
	DEBUG,
	WARNING,
	ERROR
};

void log_print(int debug_level,int rank,char* filename, int line, char *fmt,...);

#endif
