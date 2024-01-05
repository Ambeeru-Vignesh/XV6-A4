#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

struct pstat {
    int ctime;
    int etime;
    int ttime;
    int tatime;
};

int main() {
    char *commands[] = {"uniq", "head"};
    char *arguments[] = {"input.txt", "example.txt"};
    int num_commands = sizeof(commands) / sizeof(commands[0]);
    int wtime = 0, sum_of_wtime = 0, sum_of_tatime = 0;

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
	    printf(1, "Process%d",i);
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
	//printf(1, "  Turnaround time: %d\n\n", pstat_info.tatime);
	//printf(1, "  Wating time: %d\n\n", wtime);

	sum_of_wtime += wtime;
        sum_of_tatime += pstat_info.tatime;
	wtime += pstat_info.tatime;

    }

    printf(1, " Average Turnaround time using FCFS: %d\n\n", (sum_of_tatime/num_commands));
    printf(1, " Average Wating time using FCFS: %d\n\n", (sum_of_wtime/num_commands));

    exit();
}

