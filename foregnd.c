#include "header.h"

void foregnd(char cmd[], int numPar, char *par[])
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
    args[numPar + 1] = for_ctrz;

    pid_t pid;
    pid = fork();
    setChPid(pid, for_ctrz);

    if (pid < 0)
    {
        perror("Fork Failed");
        return;
    }
    if (pid == 0)
    {
        int xvpret = execvp(cmd, args);
        if (xvpret < 0)
        {
            perror("Error: command not found");
            exit(EXIT_FAILURE);
        }
        fflush(NULL);
    }
    else
    {
        int status;
        pid_t waitRet = waitpid(pid, &status, WUNTRACED);

        // write(2, "doneFork\n", strlen("doneFork\n"));
    }
    // write(2, "doneEx\n", strlen("doneEx\n"));
}