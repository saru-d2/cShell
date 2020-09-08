#include "header.h"
#include "JobStruct.h"

void backgnd(char cmd[], int numPar, char *par[], job jobArray[], int *jobIter)
{
    numPar--;
    pid_t pid, childP;
    char *args[numPar + 5];
    // strcpy(args[0], cmd);
    args[0] = cmd;
    fflush(NULL);
    for (int i = 0; i < numPar; i++)
    {
        args[i + 1] = par[i];
    }
    fflush(NULL);
    args[numPar + 1] = NULL;
    int exret = 1;
    pid = fork();
    setpgid(0, 0);
    if (pid < 0)
    {
        perror("fork failed");
    }
    else if (pid == 0)
    {
        childP = getpid();
        exret = execvp(cmd, args);
        if (exret < 0)
        {
            perror("process failed");
            return;
        }
    }
    else
    {
        printf("[%d] %d %s\n", *jobIter + 1, pid, cmd);
        jobArray[(*jobIter)].id = pid;
        strcpy(jobArray[(*jobIter)].name, cmd);
        *jobIter += 1;
    }
    return;
}