#include "header.h"
#include "JobStruct.h"

void bgProcessEnd(job *jobArr, int jobIter, char *home_dir, bool *kjobFlagPtr)
{
    pid_t pid;
    int stat;
    pid = waitpid(-1, &stat, WNOHANG);
    if (pid < 0){
        return;
    }
    
    for (int i = 0; i < jobIter; i++)
    {
        if ((jobArr[i].id == pid && WIFEXITED(stat)) || (*kjobFlagPtr == 0 && jobArr[i].id == pid) )
        {
            printf("\n");
            //debugging
            printf("%s with pid %d ", jobArr[i].name, jobArr[i].id);
            //
            int xStat = WEXITSTATUS(stat);
            if (xStat == 0)
                printf("exitted normally\n");
            else
                printf("exitted with some errors\n");

            jobArr[i].running = false;
            print_PS1(home_dir);
            fflush(NULL);
            break;
        }
    }
    return;
}