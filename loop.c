#include "header.h"
#include "JobStruct.h"
char *line_read, *breaks[100000], *cmd, *par[100000], *listOfSemiSep[100000];
ssize_t zero = 0;
job jobArr[100000];
int jobIter = 0;
char *homeDir;

void bgEnded()
{
    bgProcessEnd(jobArr, jobIter, homeDir);
}

void loop(char home_dir[])
{
    homeDir = home_dir;
    bool run = true;
    while (run)
    {
        //chk if anything ended..
        signal(SIGCHLD, bgEnded);
        printf("back\n");
        print_PS1(home_dir);
        getline(&line_read, &zero, stdin);
        // line_tokenised = strtok(line_read, " \n");
        int semiCnt = 0;
        listOfSemiSep[0] = strtok(line_read, ";\n");
        while (listOfSemiSep[semiCnt] != NULL)
        {
            listOfSemiSep[++semiCnt] = strtok(NULL, ";\n");
        }
        // printf("%d\n", semiCnt);
        for (int i = 0; i < semiCnt; i++)
        {
            // printf("%s\n", listOfSemiSep[i]);
            int tknCnt = 0;
            cmd = breaks[0] = strtok(listOfSemiSep[i], " \n");
            while (listOfSemiSep[i] != NULL)
            {
                breaks[tknCnt++] = listOfSemiSep[i];
                listOfSemiSep[i] = strtok(NULL, " \n");
            }

            for (int i = 1; i < tknCnt; i++)
            {
                par[i - 1] = breaks[i];
            }
            // printf("cmd: !%s!\n", cmd);
            int numPar = tknCnt - 1;
            bool done = false;

            if (strcmp(cmd, "quit") == 0)
            {
                run = false;
                done = true;
                break;
            }
            if (strcmp(cmd, "clear") == 0)
            {
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

            if (strcmp(cmd, "pinfo") == 0)
            {
                pinfo(par, numPar, home_dir);
                done = true;
            }

            if (!done)
            {
                if (numPar > 0 && strcmp(par[numPar - 1], "&") == 0)
                    backgnd(cmd, numPar, par, jobArr, &jobIter);
                else
                    foregnd(cmd, numPar, par);
            }
        }
    }
}
