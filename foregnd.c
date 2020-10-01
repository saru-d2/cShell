#include "header.h"
#include "JobStruct.h"

int foregnd(char cmd[], int numPar, char *par[], job jobArray[], int *jobIter)
{
    // printf("wow %s\n\n", cmd);
    // write(2, cmd, strlen(cmd));
    // write(2, "!!\n", strlen("!!\n"));
    char *args[numPar + 5];
    args[0] = cmd;
    for (int i = 0; i < numPar; i++)
        args[i + 1] = par[i];
    char for_ctrz[1000];
    strcpy(for_ctrz, "");
    int i = 0;
    while (args[i] != NULL)
    {
        strcat(for_ctrz, args[i]);
        strcat(for_ctrz, " ");
        i++;
    }
    args[numPar + 1] = NULL;

    pid_t pid;
    pid = fork();
    if (pid > 0)
        setChPid(pid, for_ctrz);

    if (pid < 0)
    {
        perror("Fork Failed");
        return -1;
    }
    if (pid == 0)
    {
        int xvpret = execvp(cmd, args);
        if (xvpret < 0)
        {
            perror("Error: command not found");
            return -1;
            // exit(EXIT_FAILURE);
        }
        fflush(NULL);
    }
    else
    {
        int status;
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);

        setpgid(pid, 0);
        tcsetpgrp(STDIN_FILENO, pid);

        pid_t waitRet = waitpid(pid, &status, WUNTRACED);

        tcsetpgrp(STDIN_FILENO, getpgrp());
        
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);

        if (WIFSTOPPED(status))
        {
            jobArray[(*jobIter)].id = pid;
            strcpy(jobArray[(*jobIter)].name, for_ctrz);
            jobArray[(*jobIter)].running = true;
            *jobIter += 1;
        }
        char nullstr[] = "\0";
        setChPid(0, nullstr);
    }
    return 1;
    // write(2, "doneEx\n", strlen("doneEx\n"));
}