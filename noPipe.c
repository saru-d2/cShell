#include "header.h"
#include "JobStruct.h"

char *cmd, *breaks[1000], *par[1000];
bool noPipe(char *line, char *home_dir, job jobArr[], int *jobIterPtr)
{
    int tknCnt = 0;
    cmd = breaks[0] = strtok(line, " \t\n");
    while (line != NULL)
    {
        breaks[tknCnt++] = line;
        line = strtok(NULL, " \t\n");
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