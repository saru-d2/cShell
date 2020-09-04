#include "header.h"
char *line_read, *line_tokenised, *tokens[100000], *cmd, *par[100000];
ssize_t zero = 0;
void loop(char home_dir[])
{
    bool run = true;
    while (run)
    {
        print_PS1(home_dir);
        getline(&line_read, &zero, stdin);
        line_tokenised = strtok(line_read, " \n");
        int tknCnt = 0;
        while (line_tokenised != NULL)
        {
            tokens[tknCnt++] = line_tokenised;
            line_tokenised = strtok(NULL, " \n");
        }
        cmd = tokens[0];
        for (int i = 1; i < tknCnt; i++)
        {
            par[i - 1] = tokens[i];
        }
        int numPar = tknCnt - 1;
        bool done = false;

        if (strcmp(cmd, "quit") == 0)
        {
            run = false;
            done = true;
            break;
        }
        if (strcmp(cmd, "clear") == 0){
            clear();
        }
        if (strcmp(cmd, "cd") == 0)
        {
            cd(numPar, par, home_dir);
            done = true;
        }

        if (strcmp(cmd, "pwd") == 0)
        {
            pwd();
            done = true;
        }

        if (strcmp(cmd, "echo") == 0)
        {
            echo(par, numPar);
            done = true;
        }

        if (strcmp(cmd, "ls") == 0)
        {
            ls(par, numPar, home_dir);
            done = true;
        }

        if (strcmp(cmd, "pinfo") == 0){
            pinfo(par, numPar, home_dir);
            done = true;
        }

        if (!done)
        {
            if (numPar > 0 && strcmp(par[numPar - 1], "&") == 0)
                backgnd(cmd, numPar, par);
            else
                foregnd(cmd, numPar, par);
        }
    }
}
