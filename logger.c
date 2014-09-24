//logger.c
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include<string.h>


FILE *fp ;

void log_print(int debug_level,int rank,char* filename, int line, char *fmt,...)
{
	va_list         list;
	char            *p, *r,*hostname;
	int             e,z,s;
	s=128;

	hostname = (char*) malloc(s*sizeof(char));

	z = gethostname(hostname, sizeof(hostname));
	if ( z == -1) {
		s*=2;
		hostname = (char*) realloc(hostname, s*sizeof(char));	
		z = gethostname(hostname, sizeof(hostname));
		if(z == -1){
			return;
		}
	}

	char* file_name = calloc(strlen(hostname)+18,sizeof(char));
	//ibvdev-hostname-rank3.log
	char rankStr[2];
	sprintf(rankStr,"%d",debug_level);
	file_name[0]='\0';
	strcat(file_name,"ibvdev-");
	strcat(file_name,hostname);
	strcat(file_name,"-rank");
	strcat(file_name,rankStr);
	strcat(file_name,".log");
	printf("filename->\t%s\n",file_name);

	fp = fopen (file_name,"a+");
	if(!fp){
		printf("file not open\n");
		return;
	}
	free(file_name);
	free(hostname);
	if(debug_level == INFO)
		fprintf(fp,"INFO\t- xdev[IBVDev] ");
	else if(debug_level == DEBUG)
		fprintf(fp,"DEBUG\t- xdev[IBVDev] ");
	else if(debug_level == WARNING)
		fprintf(fp,"WARNING\t- xdev[IBVDev] ");
	else //(debug_level == ERROR)
		fprintf(fp,"ERROR\t- xdev[IBVDev] ");
	va_start( list, fmt );
	for ( p = fmt ; *p ; ++p )
	{
		if ( *p != '%' )//If simple string
		{
			fputc( *p,fp );
		}
		else
		{
			switch ( *++p )
			{
				/* string */
			case 's':
				{
					r = va_arg( list, char * );

					fprintf(fp,"%s", r);
					continue;
				}

				/* integer */
			case 'd':
				{
					e = va_arg( list, int );

					fprintf(fp,"%d", e);
					continue;
				}


			default:
				fputc( *p, fp );
			}
		}
	}
	va_end( list );
	fprintf(fp," [%s][line: %d] ",filename,line);
	fputc( '\n', fp );
	fclose(fp);
}
