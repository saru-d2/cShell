#include "header.h"
#include "JobStruct.h"

void backgnd(char cmd[], int numPar, char *par[], job jobArray[], int *jobIter)
{
    // printf("in bgrnd\n");
    fflush(NULL);
   
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
    if (strcmp(args[numPar] , "&") == 0){
        args[numPar] = NULL;
    }
    else {
        args[numPar][strlen(args[numPar]) - 1] = '\0';
    }
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
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        char toJobArr[1000];
        int i =0;
        strcpy(toJobArr, "");
        while(args[i] != NULL){
            strcat(toJobArr, args[i]);
            strcat(toJobArr, " ");
            i++;
        }
        jobArray[(*jobIter)].id = pid;
        strcpy(jobArray[(*jobIter)].name, toJobArr);
        *jobIter += 1;
        printf("[%d] %d %s\n", *jobIter + 1, pid, toJobArr);
    }
    return;
}