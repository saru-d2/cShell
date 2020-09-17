#include "header.h"
#include "JobStruct.h"
char *line_read, *listOfSemiSep[1000], cmdLine[1000];
// char *breaks[1000], *cmd, *par[1000];
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
    historyInit();
    homeDir = home_dir;
    bool run = true;
    while (run)
    {
        //chk if anything ended..
        signal(SIGCHLD, bgEnded);
        print_PS1(home_dir);
        getline(&line_read, &zero, stdin);
        strcpy(cmdLine, line_read);
        int semiCnt = 0;
        listOfSemiSep[0] = strtok(line_read, ";\n");
        while (listOfSemiSep[semiCnt] != NULL)
        {
            listOfSemiSep[++semiCnt] = strtok(NULL, ";\n");
        }
        for (int i = 0; i < semiCnt; i++)
        {
            run = noPipe(listOfSemiSep[i], home_dir, jobArr, &jobIter);
            if (!run)break;
        }
        pushHisQ(cmdLine);
    }
}
