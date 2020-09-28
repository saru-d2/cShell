#include "header.h"
#include "JobStruct.h"
char *line_read, *listOfSemiSep[1000], *cmdLine, *toHis;
// char *breaks[1000], *cmd, *par[1000];
size_t zero = 0;
job jobArr[100000];
int jobIter = 0;
char *homeDir;
bool kjobFlag = true;

void bgEnded()
{
    // printf("some task ended\n");
    bgProcessEnd(jobArr, jobIter, homeDir, &kjobFlag);
}

void loop(char home_dir[])
{
    historyInit();
    homeDir = home_dir;
    bool run = true;
    getshPid();
    ctrlCZinit(home_dir);
    while (run)
    {
        //chk if anything ended..
        signal(SIGCHLD, bgEnded);
        //
        print_PS1(home_dir);
        int lSize = getline(&line_read, &zero, stdin);
        // for ctrl-D
        if (lSize <= 0){
            run = false;
            break;
        }
        cmdLine = line_read;
        toHis = strtok(cmdLine, "\n");
        int semiCnt = 0;
        listOfSemiSep[0] = strtok(line_read, ";\n");
        while (listOfSemiSep[semiCnt] != NULL)
        {
            listOfSemiSep[++semiCnt] = strtok(NULL, ";\n");
        }
        for (int i = 0; i < semiCnt; i++)
        {
            if (!pipeChk(listOfSemiSep[i]))
            {
                run = execCmd(listOfSemiSep[i], home_dir, jobArr, &jobIter, &kjobFlag);
            }
            else
                run = Pipe(listOfSemiSep[i], home_dir, jobArr, &jobIter, &kjobFlag);
            if (!run)
                break;
        }
        pushHisQ(toHis);
    }
}
