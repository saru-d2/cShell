#include "header.h"
#include "JobStruct.h"

int bg(int numPar, char *par[], job jobArr[], int *jobCnt)
{
    printf("bg\n");
    if (numPar != 1)
    {
        printf("Wrong number of arguments\n");
        return -1;
    }
    int num = atoi(par[0]);
    if (num < 1 || num > *jobCnt)
    {
        printf("Job doesnt exist\n");
        return -1;
    }
    num--;
    pid_t pid = jobArr[num].id;
    kill(pid, SIGTTIN);
    kill(pid, SIGCONT);
    return 1;
}

int fg(int numPar, char *par[], job jobArr[], int *jobCnt)
{
    int status;
    printf("fg\n");
    if (numPar != 1)
    {
        printf("Wrong no. of arguments");
        return -1;
    }
    int num = atoi(par[0]);
    if (num <= 0 || num > *jobCnt)
    {
        printf("Job doesn't exist\n");
        return -1;
    }
    bool done = false;
    num--;
    int pid = jobArr[num].id;
    if (pid == 0)
    {
        printf("pid didn't exist\n");
        return -1;
    }
    jobArr[num].running = false;

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);

    tcsetpgrp(STDIN_FILENO, pid);
    kill(pid, SIGCONT);

    setChPid(pid, jobArr[num].name);
    waitpid(pid, &status, WUNTRACED);

    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

    return 1;
}