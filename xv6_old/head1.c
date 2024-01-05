//head files
#include "types.h"
#include "stat.h"
#include "user.h"
#define DEFAULT_LINES 14

int main(int argc, char *argv[])
{
	int filedes=0;
    	int textlines = DEFAULT_LINES;
    	printf(1,"Head command is geing executed in kernel mode\n");
    	
	// Handle the case where the first argument is "-n"
	if (argc > 1 && strcmp(argv[1], "-n") == 0 && argc > 2)
    	{
        	textlines = atoi(argv[2]);
        	argc = argc - 2;
        	argv = argv + 2;
    	}

    	if (argc <= 1)
    	{
		char buffer[512];
        	textlines = 1;
        	// No filename provided, read from standard input
        	printf(1,"Enter input string : \n");
		read(filedes,buffer,sizeof(buffer));
        	head1(buffer, textlines);
    	}
    	else
    	{
        	//handles if multiple text files are mentioned
        	for (int i = 1; i < argc; i++)
        	{
                	//int filedes;
            		if ((filedes = open(argv[i], 0)) < 0)
            		{
                		printf(2, "head: cannot open %s\n", argv[i]);
                		exit();
            		}
            		if (argc > 2)
            		{
                		printf(1, " ----- %s -----\n", argv[i]);
            		}
	    		
			char buffer[512];
    			read(filedes, buffer, sizeof(buffer));
    			head1(buffer,textlines);
            		close(filedes);
        	}
    	}

    exit();
}
