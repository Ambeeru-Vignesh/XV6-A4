//Headfiles
#include "types.h"
#include "stat.h"
#include "user.h"
//using the maxmium length (we can use direct numeric if required) 
#define MAX_LINE_LENGTH 1000

int main(int argc, char *argv[]) 
{
	//checking whether the user has passed the arguments
	if (argc <= 1)
    	{
		printf(1, "Usage: %s <program_name> <inputFile.txt>\n", argv[0]);
	    	exit();
    	}

	//initialzating variable
    	char *inputFile;
    	char buffer[1024];
    	char cond[10];

	//checking if whether the user has enter only the filename or (-i,-c,-d)
    	if (argc > 2)
	{
		inputFile = argv[2];
		strcpy(cond,argv[1]);
    	}
	else
	{
    		inputFile = argv[1];
	}

   	// Store input file name from the command line
   	int fileDescriptor = open(inputFile, 0);

	//check if opening the file failed
    	if (fileDescriptor < 0)
    	{
		printf(1, "Error: Cannot open file %s\n", inputFile); 
        	exit();
    	}

	//instead of passing the text string i am passing the integer to kernel comparing the number insted of string
    	int flag=0;
  	if (strcmp(cond,"-i") == 0)
	{
		flag=1;
	}
	else if(strcmp(cond,"-d") == 0)
	{
		flag=2;
	}
	else if(strcmp(cond,"-c") == 0)
	{
		flag=3;
	}

    	printf(1, "Uniq command is being executed in kernel mode\n");

	read(fileDescriptor,buffer,sizeof(buffer));
	
	//calling the sys_uniq1() present in the kernel sysproc.c
	uniq1(buffer,flag);
    	close(fileDescriptor);
    	exit(); 
}
