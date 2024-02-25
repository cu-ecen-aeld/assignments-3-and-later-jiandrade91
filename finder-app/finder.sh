test@Ubuntu:~/Desktop/ecea5305/finder-app$ cat finder.sh 
#/bin/bash
#########################################################################################
#Julian Andrade 2024.01.28								#
#Of the form:  finder.sh <argument1> <argument2>					#
#argument 1 = 	filesdir	= File path to a dir					#
#argument 2 =	searchstr	= Text string to be searched within files		#
#1.) return value 1 error and print message if either statments were not specified	#
#2.)return value 1 error and print message if FILESDIR isnt a DIR			#
#3.) Print: # of files are X and # of matching lines are Y. Match is == SEARCHSTR	#
#Example invocation:									#	
#		finder.sh /tmp/aesd/assignment1 linux					#
#########################################################################################
#Code START

#Define 2 arguments
filesdir=$1		#argument 1
searchstr=$2		#argument 2

#Check to make sure both arguments specified
if [ -n "$2" ]		#checks that there are two aruments
then
	echo "success"
	#exit 0 #used to test first part
else
	echo "ERROR: Invalid Number of Arguments.
	Total number of argements should be 2.
	The order of the arguments should be:
		1.)File Directory Path
		2.)String to be searched in path in #1"
	exit 1
fi

#Check to see if argument 1 (FILESDIR) is actually a DIR. Print message if not
if [ -d "$filesdir" ]
then
	echo "$filesdir exists and is a DIR! :)"
	#exit 0 #used to test sesecond loop
else
	#echo "$filesdir is not a DIR or doesnt exist. :("
	exit 1
fi

#Count all files in directory
x=$(ls $filesdir | wc -l) 		# wc -l adds a count for how many files found by ls

#Count all lines in files in DIR if they contain the string $SEARCHSTR from arg2
y=$(grep -r $searchstr $filesdir | wc -l)	#wc -l adds a count for search success from grep seaching $searchstr in DIR $filesdir 

#print out the # of files and matching lines
echo "The number of files are $x and the number of matching lines are $y"

