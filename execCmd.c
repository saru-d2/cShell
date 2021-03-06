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

int execCmd(char *line, char *home_dir, job jobArr[], int *jobIterPtr, bool *kjobFlag)
{
    char *cmd, *breaks[1000], *par[1000];
    // write(2, "!", strlen("!"));
    // write(2, line, strlen(line));
    // write(2, "!\n", strlen("!\n"));
    fflush(NULL);
    // bool flags[3] = {0, 0, 0};
    int tknCnt = 0;
    int exitCode;
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
            if (b == 1) // <
            {
                int inFdr = open(breaks[i], O_RDONLY);
                if (inFdr < 0)
                {
                    perror("open");
                    return false;
                }
                dup2(inFdr, STDIN_FILENO);
                close(inFdr);
            }
            else if (b == 2) // >
            {
                int outFdr = open(breaks[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                // printf("@%d\n@", outFdr);
                if (outFdr < 0)
                {
                    perror("open");
                    return false;
                }
                dup2(outFdr, STDOUT_FILENO);
                close(outFdr);
            }
            else if (b == 3) // >>
            {
                int outFdr = open(breaks[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (outFdr < 0)
                {
                    perror("open");
                    return false;
                }
                dup2(outFdr, STDOUT_FILENO);
                close(outFdr);
            }
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
        overkill(numPar, par, jobArr, jobIterPtr);
        quit();
        return -2;
    }

    else if (strcmp(cmd, "clear") == 0)
        exitCode = clear();
    else if (strcmp(cmd, "cd") == 0)
        exitCode = cd(numPar, par, home_dir);
    else if (strcmp(cmd, "pwd") == 0)
        exitCode = pwd();
    else if (strcmp(cmd, "echo") == 0)
        exitCode = echo(par, numPar);
    else if (strcmp(cmd, "ls") == 0)
        exitCode = ls(par, numPar, home_dir);
    else if (strcmp(cmd, "pinfo") == 0)
        exitCode = pinfo(par, numPar, home_dir);
    else if (strcmp(cmd, "history") == 0)
        exitCode = printHis(numPar, par);
    else if (strcmp(cmd, "nightswatch") == 0)
        exitCode = nightswatch(numPar, par);
    else if (strcmp(cmd, "jobs") == 0)
        exitCode = jobs(numPar, par, jobArr, jobIterPtr);
    else if (strcmp(cmd, "unsetenv") == 0)
        exitCode = unSetVar(numPar, par);
    else if (strcmp(cmd, "setenv") == 0)
        exitCode = setVar(numPar, par);
    else if (strcmp(cmd, "kjob") == 0)
        exitCode = kjob(numPar, par, jobArr, jobIterPtr, kjobFlag);
    else if (strcmp(cmd, "overkill") == 0)
        exitCode = overkill(numPar, par, jobArr, jobIterPtr);
    else if (strcmp(cmd, "fg") == 0)
        exitCode = fg(numPar, par, jobArr, jobIterPtr);
    else if (strcmp(cmd, "bg") == 0)
        exitCode = bg(numPar, par, jobArr, jobIterPtr);
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
            exitCode = backgnd(cmd, numPar, par, jobArr, jobIterPtr);
        else
            exitCode = foregnd(cmd, numPar, par, jobArr, jobIterPtr);
    }
    dup2(oldStdin, STDIN_FILENO);
    dup2(oldStdin, STDOUT_FILENO);
    // printf("done\n");
    close(oldStdout);
    close(oldStdin);
    // write(2, "done\n", strlen("done\n"));
    return exitCode;
}