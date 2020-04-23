#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <getopt.h>

int main()
{
        char *argv1[8] = {" ","--seed","3","--array_size", "100","--pnum","4",NULL};
        char *argv2[9] = {" ","--seed","3","--array_size", "100","--pnum","4","-f",NULL};

        int pid = fork();
        if(pid==0)
                {
                        execv("parallel_min_max",argv1);
                        return 0;
                }

        int pid2 = fork();
        if(pid2==0)
        {
                execv("parallel_min_max",argv2);
                return 0;
        }
	for(int i = 0;i<2;i++)
		wait(NULL);
        printf("\n Exec task done!\n");
        return 0;
}

