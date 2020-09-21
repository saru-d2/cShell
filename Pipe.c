#include "header.h"
#include "JobStruct.h"

bool execCmd(char *line, char *home_dir, job jobArr[], int *jobIterPtr)
{
    char *cmd, *breaks[1000], *par[1000];
    int tknCnt = 0;
    cmd = breaks[0] = strtok(line, " \t\r\n");
    while (line != NULL)
    {
        breaks[tknCnt++] = line;
        line = strtok(NULL, " \t\r\n");
    }
    for (int i = 1; i < tknCnt; i++)
    {
        par[i - 1] = breaks[i];
    }
    int numPar = tknCnt - 1;
    if (strcmp(cmd, "quit") == 0 || strcmp(cmd, "exit") == 0)
    {
        return false;
    }
    else if (strcmp(cmd, "clear") == 0)
        clear();
    else if (strcmp(cmd, "cd") == 0)
        cd(numPar, par, home_dir);
    else if (strcmp(cmd, "pwd") == 0)
        pwd();
    else if (strcmp(cmd, "echo") == 0)
        echo(par, numPar);
    else if (strcmp(cmd, "ls") == 0)
        ls(par, numPar, home_dir);
    else if (strcmp(cmd, "pinfo") == 0)
        pinfo(par, numPar, home_dir);
    else if (strcmp(cmd, "history") == 0)
        printHis(numPar, par);
    else if (strcmp(cmd, "nightswatch") == 0)
        nightswatch(numPar, par);
    else
    {
        char c;
        if (numPar == 0)
        {
            c = cmd[strlen(cmd) - 1];
        }
        else
            c = par[numPar - 1][strlen(par[numPar - 1]) - 1];
        if (c == '&')
            backgnd(cmd, numPar, par, jobArr, jobIterPtr);
        else
            foregnd(cmd, numPar, par);
    }
    return true;
}

bool Pipe(char *line, char *home_dir, job jobArr[], int *jobIterPtr)
{

    int numPipeSep = 0;
    char *pipeSep[1000];
    pipeSep[0] = strtok(line, "|");
    while (line != NULL)
    {
        pipeSep[numPipeSep++] = line;
        line = strtok(NULL, "|");
    }
    int oldStdin = dup(STDIN_FILENO);
    int oldStdout = dup(STDOUT_FILENO);
    printf("%d\n", numPipeSep);

    // creating all pipes
    int fdPipe[(numPipeSep + 1) * 2];
    for (int i = 0; i < numPipeSep; i++)
    {
        int pret = pipe(fdPipe + i * 2);
        if (pret < 0)
        {
            perror("pipe not formed");
            exit(0);
        }
    }
    int dup2Ret;
    for (int i = 0; i < numPipeSep; i++)
    {
        if (i > 0)
        {
            dup2Ret = dup2(STDIN_FILENO,fdPipe[2 * (i - 1)]);
            if (dup2Ret < 0)
            {
                perror("pipe, dup2 failed");
                exit(0);
            }
            close(fdPipe[2 * (i - 1)]);
        }

        if (i < numPipeSep - 1)
        {
            dup2Ret = dup2(STDOUT_FILENO, fdPipe[(2 * i) + 1]);
            if (dup2Ret < 0)
            {
                perror("pipe, dup2 failed");
                exit(0);
            }
            close(fdPipe[(2 * i) + 1]);
        }
        bool exRet = execCmd(pipeSep[i], home_dir, jobArr, jobIterPtr);
        dup2(oldStdin, STDIN_FILENO);
        dup2(oldStdin, STDOUT_FILENO);
        if (!exRet)
            return false;
    }

    return true;
}