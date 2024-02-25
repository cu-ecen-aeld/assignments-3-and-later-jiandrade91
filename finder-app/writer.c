/*
 ************************	NOTES		*******************************************
 * Julian Andrade 2024.02.11
 * 	writer.c Requirements (From Assignment 1)
 * 1.) Accepts 2 arguments:
 *  	a.) Full File path on the filesystem (including filename); called "writefile"
 *  	b.) String to be written to file; called "writestr"
 * 2.) Exits with Value 1 Error && prints statements if not enough arguments
 * 3.) Creats new file with name and path fromt "writefile" with contents "writestr" if file
 * and/or path dont exist.
 * 	Addendum for Assignment 2:
 * 3.) [EDIT] Do not including making a directory that doesnt exist
 * 4.) Setup and use syslog logging; Use "LOG_USER" facility
 * 5.) Use syslog to write message "Writing <string> to <file>" where <string> is the text 
 * string written to file (second argument) and <file> is the file created by the script.  
 * This should be written with "LOG_DEBUG" level.
 * 6.) Log any unexpected errors with "LOG_ERR" level
 *
 *************************	CODE START	******************************************
 */
#include <stdio.h>
#include <syslog.h>


int main(int argc, char *argv[]){
	
	//1st argument (2nd in char array) = filepath + file name
	//2nd argumnet (3rd in char array) = string to write in file name
	char *writefile = argv[1];
	char *writestr = argv[2];
	
	//Open connection to system error logging using "openlog()"
	//syslog using the "LOG_USER" facility required for homework
	//HOW TO USE: void openlog(const char *ident, int option, int facility);
	openlog(NULL,LOG_PID,LOG_USER);


	//if there are not at least 3 arguments, return error
	//argc = argument count; includes the program name as first argument
	//Need to call syslog()
	//HOW TO USE: void syslog (int facility_priority, char *format, ...)
	if (argc < 3)
	{
		syslog(LOG_ERR,"%d arguments specified.\n",argc);
		printf("Not enough arguments.Please provide the following: \n<full/path/to/file.txt> <String_to_write_to_file>");
		return 1;
	}
	//Use "FILE *fopen(const char *filename, const char *mode)"  to open/make a new file
	else{
		//first line creates placeholder for newfile
		FILE *newfile;
		//newfile gets fopen. Passes in name of file (+ filepath) 
		newfile = fopen(writefile,"w+");
		//write to the file we just opened
		fprintf(newfile,"%s\n", writestr);
		fclose(newfile);
		
		//report syslog write message (#5 above) at "LOG_DEBUG" level
		//should contain "Writing <string> to <file>"
		syslog(LOG_DEBUG,"Writing %s to %s",writestr, writefile);

		return 0;

	}
	
}



