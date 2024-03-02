#include "systemcalls.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
=======
>>>>>>> assignments-base/assignment4
||||||| c93ab2a
=======
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
>>>>>>> fba2e58ad3d21857af7a1ed8df42a287a6ea3dab

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{

/*
 * TODO  add your code here
 *  Call the system() function with the command set in the cmd
 *   and return a boolean true if the system() call completed with success
 *   or false() if it returned a failure
*/
<<<<<<< HEAD
<<<<<<< HEAD
    int returncode;
    returncode = system(cmd);
    if (returncode == -1){
        return false;
    } else if (returncode == 0){
	return true;
    } else {exit(EXIT_SUCCESS);}   
=======

    return true;
>>>>>>> assignments-base/assignment4
||||||| c93ab2a

    return true;
=======
    int returncode;
    returncode = system(cmd);
    if (returncode == -1){
        return false;
    } else if (returncode == 0){
	return true;
    } else {exit(EXIT_SUCCESS);}   
>>>>>>> fba2e58ad3d21857af7a1ed8df42a287a6ea3dab
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];

/*
 * TODO:
 *   Execute a system command by calling fork, execv(),
 *   and wait instead of system (see LSP page 161).
 *   Use the command[0] as the full path to the command to execute
 *   (first argument to execv), and use the remaining arguments
 *   as second argument to the execv() command.
 *
*/
<<<<<<< HEAD
<<<<<<< HEAD
    pid_t process_id;
    int status;
    process_id = fork();
    if(process_id == -1){ return false;} 
    else if (process_id == 0){
	    status = execv(command[0],command);
	    if (status == -1){
	    	exit(EXIT_FAILURE);
	    }
	    else {wait(&status);}
    }
    if (wait(&status) == -1){
	    return false;
    }
    if (WIFEXITED(status)){ 
	    if (WEXITSTATUS(status)){return false;}
    }
    else {return false;}
=======
>>>>>>> assignments-base/assignment4
||||||| c93ab2a
=======
    pid_t process_id;
    int status;
    process_id = fork();
    if(process_id == -1){ return false;} 
    else if (process_id == 0){
	    status = execv(command[0],command);
	    if (status == -1){
	    	exit(EXIT_FAILURE);
	    }
	    else {wait(&status);}
    }
    if (wait(&status) == -1){
	    return false;
    }
    if (WIFEXITED(status)){ 
	    if (WEXITSTATUS(status)){return false;}
    }
    else {return false;}
>>>>>>> fba2e58ad3d21857af7a1ed8df42a287a6ea3dab

    va_end(args);

    return true;
}

/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];


/*
 * TODO
 *   Call execv, but first using https://stackoverflow.com/a/13784315/1446624 as a refernce,
 *   redirect standard out to a file specified by outputfile.
 *   The rest of the behaviour is same as do_exec()
 *
*/
<<<<<<< HEAD
<<<<<<< HEAD
    
    pid_t process_id;
    int status;
    int fd = open(outputfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (fd <= 0) { perror("open"); abort(); }
    switch (process_id = fork()){
	case -1: return false;
	case 0:
		 if (dup2(fd, 1) < 0) { perror("dup2"); abort(); }
		 close(fd);
		 if( execv(command[0],command) == -1){
    		 	close(fd); return false;	
		 }
		 int child_proc = execv(command[0],command);
            	 if (child_proc == -1 || child_proc == 2){
                 close(fd);return false;
            	 }
            	 else {close(fd); return true;}

	default:
		close(fd);
    }
    if (wait(&status) == -1){
	    return false;
    }
    close(fd);
=======
||||||| c93ab2a
=======
    
    pid_t process_id;
    int status;
    int fd = open(outputfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (fd <= 0) { perror("open"); abort(); }
    switch (process_id = fork()){
	case -1: return false;
	case 0:
		 if (dup2(fd, 1) < 0) { perror("dup2"); abort(); }
		 close(fd);
		 if( execv(command[0],command) == -1){
    		 	close(fd); return false;	
		 }
		 int child_proc = execv(command[0],command);
            	 if (child_proc == -1 || child_proc == 2){
                 close(fd);return false;
            	 }
            	 else {close(fd); return true;}
>>>>>>> fba2e58ad3d21857af7a1ed8df42a287a6ea3dab

<<<<<<< HEAD
>>>>>>> assignments-base/assignment4
||||||| c93ab2a
=======
	default:
		close(fd);
    }
    if (wait(&status) == -1){
	    return false;
    }
    close(fd);
>>>>>>> fba2e58ad3d21857af7a1ed8df42a287a6ea3dab
    va_end(args);

    return true;
}
