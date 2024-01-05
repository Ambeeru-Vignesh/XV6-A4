//Headfiles
#include "types.h"
#include "stat.h"
#include "user.h"

//using the maxmium length (we can use direct numeric if required) 
#define MAX_LINE_LENGTH 1000

int main(int argc, char *argv[]) {
	if (argc <= 1)  // Check if the number of command-line arguments is not equal to 2
	{
		printf(1, "Usage: %s <program_name> <inputFile.txt>\n", argv[0]);
		exit();
    	}
	char *inputFile;
	char cond[10];
	if (argc > 2)
	{
		inputFile = argv[2];
		strcpy(cond,argv[1]);
	}
	else
	{
		inputFile = argv[1];
	}

    	//initialization and assign values
   	// Store input file name from the command line
	int fileDescriptor = open(inputFile, 0);
	char previousLine[MAX_LINE_LENGTH] = ""; 
	char currentLine[MAX_LINE_LENGTH]; 
	char cmpLine[MAX_LINE_LENGTH];
	char currentCharacter;
	int count=0; 
	if (fileDescriptor < 0) // Check if opening the file failed
	{
		printf(1, "Error: Cannot open file %s\n", inputFile); 
        	exit();
   	}

    	printf(1, "Uniq command is being executed in user mode\n");
	int value = 0;
    	while (read(fileDescriptor, &currentCharacter, 1) == 1)  // Read one character at a time from the file to compare the previous and current line
    	{
		currentLine[value] = currentCharacter;
		value += 1;
	    // Check for newline character
        	if (currentCharacter == '\n') 
		{
	    		currentLine[value] = '\0'; // Null-terminate the current line
			if (strcmp(cond,"-i") == 0)
			{
                    		strcpy(cmpLine, currentLine);
                    		for (int i = 0; cmpLine[i]!='\0'; i++)
		    		{
                        		if(cmpLine[i] >= 'A' && cmpLine[i] <= 'Z')
					{
			               		cmpLine[i] = cmpLine[i] + 32;
					}	
                  		}		
                    		if (strcmp(previousLine, cmpLine) != 0)
				{
                        		printf(1,"%s", currentLine); //Displaying the unique line
                        		strcpy(previousLine, cmpLine);
                  		}
            		}
            		else if(strcmp(cond,"-d") == 0)
			{
                		if (strcmp(previousLine,currentLine) == 0)
				{
                        		++count;
                            		if (count == 1)
					{
                            			printf(1,"%s", currentLine);
                            		}
                    		}	
                    
				else
				{
                        		count = 0;
                    		}
                        	strcpy(previousLine,currentLine);
			}
            		else if(strcmp(cond,"-c") == 0)
			{

                		if ((strcmp(previousLine,currentLine) == 0) || (strcmp(previousLine,"") == 0))
				{
                        		count++;
                		}
                		else
				{	
                        		printf(1,"%d %s",count, previousLine);
                        		count = 1;
                		}
                		strcpy(previousLine, currentLine);
            		}
			else 
			{
				if (strcmp(currentLine, previousLine) != 0)
            			// Check if the current line is different from the previous line 
	    			{
                			printf(1, "%s", currentLine); // Print the current line
                			strcpy(previousLine, currentLine); // Copy the current line to the previous line buffer
            			}

			}	

		value = 0;
    		}
	}
	close(fileDescriptor);
    	exit(); 
}

