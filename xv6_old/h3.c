#include "types.h" //header files
#include "stat.h"
#include "user.h"
#define DEFAULT_LINES 14

#define SYS_readfiles 22



void head(int filedes, int textlines) //head function
{ 
    char buffer[512];
    int n, count = 0;
    // Read from the file or stdin until 'textlines' lines are read.
    while ((n = read(filedes, buffer, sizeof(buffer))) > 0 && count < textlines) 
    {
        for (int i = 0; i < n && count < textlines; i++) 
	{
            // Write one character at a time to stdout (fd).
            if (write(1, &buffer[i], 1) != 1) 
	    {            
                printf(2, "head: write error\n");
                exit();
            }
            // If a newline character is encountered, increment the line count.	    
            if (buffer[i] == '\n')
                count++;
        }
    }
}


int main(int argc, char *argv[]) 
{
    int textlines = DEFAULT_LINES;

    printf(1,"Head command is geing executed in user mode\n");
    if (argc > 1 && strcmp(argv[1], "-n") == 0 && argc > 2) 
    {
     	// Handle the case where the first argument is "-n"
        textlines = atoi(argv[2]);
        argc = argc - 2;
        argv = argv + 2;
    }

    if (argc <= 1) 
    {
	textlines = 1;
        // No filename provided, read from standard input
        printf(1,"Enter input string : \n");
	head(0, textlines);

    } 
    else 
    {
	//handles if multiple text files are mentioned    
        for (int i = 1; i < argc; i++) 
	{
		int filedes;
            if ((filedes = open(argv[i], 0)) < 0) 
	    {
                printf(2, "head: cannot open %s\n", argv[i]);
                exit();
            }
            if (argc > 2)
	    {
                printf(1, " ----- %s -----\n", argv[i]);
            }
            head(filedes, textlines);
            close(filedes);
        }
    }

    exit();
}
