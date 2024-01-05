#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

struct pstat {
    int ctime;
    int etime;
    int ttime;
    int tatime;
    int awtime;
};

int main() {
    char *commands[] = {"uniq", "head"};
    char *arguments[] = {"input.txt", "file.txt"};
    int num_commands = sizeof(commands) / sizeof(commands[0]);

    for (int i = 0; i < num_commands; i++) 
    {
    	int cpid;
        struct pstat pstat_info;

        // creating a child process
        cpid = fork();
        if (cpid < 0) 
	{
            printf(1, "fork failed to create\n");
            exit();
        }
        if (cpid == 0) 
	{
	    // This is the child process
            char *args[] = {commands[i], arguments[i], 0};
            exec(args[0], args);
            printf(1, "exec %s failed for the process\n", commands[i]);
            exit();
        }
	else 
	{
            if (procstat(cpid, &pstat_info) < 0) 
	    {
                printf(1, "procstat failed\n");
                exit();
            }
        }

	//printing the statistics of the process.
        printf(1, "\nProcess statistics for '%s %s':\n", commands[i], arguments[i]);
        printf(1, "  Creation time: %d\n", pstat_info.ctime);
        printf(1, "  End time: %d\n", pstat_info.etime);
        printf(1, "  Total time: %d\n\n", pstat_info.ttime);
    }

    exit();
}

