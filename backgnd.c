#include "header.h"

void backgnd(char cmd[], int numPar, char *par[])
{
    printf("in backgrnd.c\n");
    pid_t pid;
    char *args[100000];
    strcpy(args[0], cmd);
    for (int i =0; i<numPar; i++){
        strcpy(args[i+1], par[i]);
    }
    args[numPar + 1] = NULL;
    pid = fork();
    if (pid < 0){
        perror("fork failed");
    }
    else if (pid == 0){
        int exret = execvp(cmd, args);
        if (exret < 0){
            perror("process failed");
        return;
        }
    }
    else {

    }
    return;
}