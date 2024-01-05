#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

#include "pstat.h"

//uniq program
int
sys_uniq1(void)
{
	//initalization of variables
	char *buffer;
	int flag;
        if(argstr(0,&buffer)<0 || argint(1,&flag)<0)
        {
                cprintf("unable to read the buffer"); 
		return -1;
        }
    	char file[1000];	
    	char previousLine[1000] = {0};
    	char currentLine[1000]={0};
    	char cmpLine[1000]={0};
    	char currentCharacter;
   	int count=0,i;
        int value = 0;
 	
	strncpy(file,buffer,sizeof(file));
	
	for(i=0;i<sizeof(file);i++)  // Read the file to compare the previous and current line
    	{
		currentLine[value] = file[i];
	    	currentCharacter = file[i];
            	value += 1;
            	// Check for newline character
        	if (currentCharacter == '\n')
        	{
            		currentLine[value] = '\0'; // Null-terminate the current line
        		if (flag==1) 
                        {
                    		strncpy(cmpLine, currentLine,sizeof(currentLine));
                    		for (int i = 0; cmpLine[i]!='\0'; i++)
                    		{
                        		if(cmpLine[i] >= 'A' && cmpLine[i] <= 'Z')
                        		{                
						cmpLine[i] = cmpLine[i] + 32;

                        		}
                  		}
                    		if (strncmp(previousLine, cmpLine,sizeof(cmpLine)) != 0)
				{
                        		cprintf("%s", currentLine); //Displaying the unique line
                        		strncpy(previousLine, cmpLine,sizeof(cmpLine));
                  		}
            		}
	    		else if(flag==2)
			{
                    		if (strncmp(previousLine,currentLine,sizeof(currentLine)) == 0)
				{
                            		++count;
                            		if (count == 1)
					{
                            			cprintf("%s", currentLine);
                            		}
                    		}
                    		else
				{
                        		count = 0;
                    		}
                        	strncpy(previousLine,currentLine,sizeof(previousLine));

            		}		
            		else if(flag==3)
			{
                		if ((strncmp(previousLine,currentLine,sizeof(currentLine)) == 0) || (strncmp(previousLine,"",sizeof(1)) == 0))
				{
                        		count++;
                		}
                		else
				{
                        		cprintf("%d %s",count, currentLine);
                        		count = 1;
                		}
                		strncpy(previousLine, currentLine,sizeof(currentLine));
            		}
	     		 else
        		{
                		if (strncmp(currentLine, previousLine,sizeof(currentLine)) != 0)
            			// Check if the current line is different from the previous line
            			{
                			cprintf( "%s", currentLine); // Print the current line
                			strncpy(previousLine, currentLine,sizeof(currentLine)); // Copy the current line to the previous line buffer
            			}
        		}		
        		value = 0;
    		}
	}
	return 0;
}

int
sys_head1(void)
{
	char *buffer;
	int textLines;

	if(argstr(0,&buffer)<0 || argint(1,&textLines)<0)
	{
		cprintf("unable to read the file"); 
		return -1;
	}
	char file1[500]={0}, file2[500]={0};
	int j=0,lineCount=0;
	strncpy(file1,buffer,sizeof(file1));
	for(int i=0;i<sizeof(file1);i++)
	{
		file2[j++]=file1[i];
		if(file1[i]=='\n')
		{
			cprintf("%s",file2);
			j=0;
			lineCount++;
			memset(file2,0,sizeof(file2));
		}
		if(lineCount == textLines)
		{
			break;
		}
	

	}
	return 0;
}


//Assignment two

int
sys_procstat(void) {
  int pid;
  struct pstat *pstat;
  if (argint(0, &pid) < 0 || argptr(1, (void*)&pstat, sizeof(*pstat)) < 0)
    return -1;
  return procstat(pid, pstat);
}

int
sys_ps(void)
{
  return ps();
}


		
	
	
int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
