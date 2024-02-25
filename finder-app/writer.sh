test@Ubuntu:~/Desktop/ecea5305/finder-app$ cat writer.sh 
#/bin/bash
##############################################
#Julian Andrade 2024.01.28
#Accepts the following arguments: the first argument is a full path 
#to a file (including filename) on the filesystem, referred to below 
#as writefile; the second argument is a text string which will be 
#written within this file, referred to below as writestr
#
#Exits with value 1 error and print statements if any of the arguments 
#above were not specified
#
#Creates a new file with name and path writefile with content writestr, 
#overwriting any existing file and creating the path if it doesn’t 
#exist. Exits with value 1 and error print statement if the file could 
#not be created.
#
#Example:
#       writer.sh /tmp/aesd/assignment1/sample.txt ios
################################################
#Code START
#defining 2 arguments
WRITEFILE=$1		#full path to a file (including file name)
WRITESTR=$2		#text string to be written to file

#check to make sure both arguments are there
if [ -n "$2" ]
then
	echo "SUCCESS: Correct Number of Arg found"
	#exit 0		#used for testing this section
else
	echo "ERROR: Invalid Number of Arguments.
	Total number of arguments should be 2.
	The order of the arguments should be:
		1.)File Directory Path, including name
		2.)String to be written to file in path in #1"
	exit 1
fi

#checking if directory exists, if not create:
if [ -d "$(dirname "$1")" ]
then
	echo "Directory Check SUCCESS: DIR Exists and is a DIR"
	#exit 0		#used for testing this section
else
	echo "Directory Check ERROR: DIR Doesnt exist!! Creating DIR"
	mkdir -p "$(dirname "$1")"
	#exit 1		#used for testing
fi

#create a file if it doesnt exist or overwrite if does. Write $WRITESTR to this file
echo "$WRITESTR" > $WRITEFILE
echo "SUCCESS:$WRITESTR was written to $WRITEFILE"


