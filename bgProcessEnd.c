#include "header.h"
#include "JobStruct.h"

void bgProcessEnd(job *jobArr, int jobIter, char *home_dir)
{
    pid_t pid;
    int stat;
    pid = waitpid(-1, &stat, WNOHANG);
    if (pid < 0)
    {
        return;
    }
    //debugging
    // printf("pid: %d\n", pid);
    // printf("%d ", jobIter);
    //
    for (int i = 0; i < jobIter; i++)
    {
        // printf("%d !%s! ?%d?\n",i, jobArr[i].name, jobArr[i].id);
        if (jobArr[i].id == pid && WIFEXITED(stat))
        {
            printf("\n");
            //debugging
            printf("%s with pid %d ", jobArr[i].name, jobArr[i].id);
            //
            int xStat = WEXITSTATUS(stat);
            if (xStat == 0)
                printf("exited normally\n");
            else
                printf("exited with some errors\n");
            print_PS1(home_dir);
            fflush(NULL);
            break;
        }
    }
    return;
}