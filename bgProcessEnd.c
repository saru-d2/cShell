#include "header.h"
#include "JobStruct.h"

bool overkillflag = false;

void bgProcessEnd(job *jobArr, int *jobIter, char *home_dir, bool *kjobFlagPtr)
{
    printf("hello\n");
    pid_t pid;
    int stat;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
        if (pid <= 0)
        {
            return;
        }
        for (int i = 0; i < *jobIter; i++)
        {
            // printf("%d  ", jobArr[i].id);
            if (((jobArr[i].id == pid && WIFEXITED(stat)) || (*kjobFlagPtr == 0 && jobArr[i].id == pid)) || overkillflag)
                if (jobArr[i].running)
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
                    if (xStat == 0)xStat++;else xStat = -1;
                    print_PS1(home_dir, xStat);
                    fflush(NULL);
                    jobArr[i].running = false;

                    break;
                }
        }
    }

    if (overkillflag)
        *jobIter = false;
    overkillflag = false;
    return;
}

void overKillFlagTrue()
{
    overkillflag = true;
}