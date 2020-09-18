#include "header.h"
#include "JobStruct.h"

int redirectedSym(char *st)
{
    if (strcmp(st, "<") == 0)
        return 1;
    if (strcmp(st, ">") == 0)
        return 2;
    if (strcmp(st, ">>") == 0)
        return 3;
    return 0;
}

bool flags[3] = {0, 0, 0};
char *cmd, *breaks[1000], *par[1000];
bool noPipe(char *line, char *home_dir, job jobArr[], int *jobIterPtr)
{
    int tknCnt = 0;
    cmd = breaks[0] = strtok(line, " \t\r\n");
    while (line != NULL)
    {
        breaks[tknCnt++] = line;
        line = strtok(NULL, " \t\r\n");
    }
    int oldStdin = dup(STDIN_FILENO);
    int oldStdout = dup(STDOUT_FILENO);

    int numPar = 0;
    for (int i = 1; i < tknCnt; i++)
    {
        int a = redirectedSym(breaks[i]);
        int b = redirectedSym(breaks[i - 1]);
        if (a > 0)
            continue;
        if (b > 0)
        {
            if (flags[b - 1] == false)
            {
                if (b == 2 && flags[2] == true)
                    continue;
                if (b == 3 && flags[2] == true)
                    continue;

                flags[b - 1] = true;
                //flagStuffhere...
                if (b == 1) //<
                {
                    int inFdr = open(breaks[i], O_RDONLY);
                    if (inFdr < 0)
                    {
                        perror("redirection");
                        return true;
                    }
                    dup2(inFdr, STDIN_FILENO);
                }
                else if (b == 2) // >
                {
                    int outFdr = open(breaks[i], O_WRONLY | O_CREAT | O_TRUNC);
                    if (outFdr < 0)
                    {
                        perror("redirection");
                        return true;
                    }
                    dup2(outFdr, STDOUT_FILENO);
                }
                else //>>
                {
                    int outFdr = open(breaks[i], O_WRONLY | O_CREAT | O_APPEND);
                    if (outFdr < 0)
                    {
                        perror("redirection");
                        return true;
                    }
                    dup2(outFdr, STDOUT_FILENO);
                }
            }
            else
                continue;
        }
        else
        {
            par[numPar++] = breaks[i];
        }
    }

    if (strcmp(cmd, "quit") == 0 || strcmp(cmd, "exit") == 0)
    {
        dup2(oldStdin, STDIN_FILENO);
        dup2(oldStdin, STDOUT_FILENO);
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
    dup2(oldStdin, STDIN_FILENO);
    dup2(oldStdin, STDOUT_FILENO);
    return true;
}