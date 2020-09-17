#include "header.h"

void foregnd(char cmd[], int numPar, char *par[])
{
    printf("in fgrnd\n");
    char *args[numPar + 5];
    args[0] = cmd;
    for (int i = 0; i < numPar; i++)
        args[i+1] = par[i];
    args[numPar + 1] = NULL;

    pid_t pid;
    pid = fork();

    if (pid < 0){
        perror("Fork Failed");
        return;
    }
    if (pid == 0){
        int xvpret = execvp(cmd, args);
        if (xvpret < 0){
            perror("Error: command not found");
            exit(EXIT_FAILURE);
        }
    }
    else {
        int status;
        waitpid(pid, &status, WUNTRACED);
    }
}