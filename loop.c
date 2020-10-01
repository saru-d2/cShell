#include "header.h"
#include "JobStruct.h"
char *line_read, *listOfSemiSep[1000], *cmdLine, *toHis;
// char *breaks[1000], *cmd, *par[1000];
size_t zero = 0;
job jobArr[100000];
int jobIter = 0;
char *homeDir;
bool kjobFlag = true;
bool run = true;

void bgEnded()
{
    bgProcessEnd(jobArr, jobIter, homeDir, &kjobFlag);
}

void addToJobArr(pid_t id, char *name)
{
    printf("!%s!\n\n", name);
    jobArr[jobIter].id = id;
    strcpy(jobArr[jobIter].name, name);
    jobArr[jobIter].running = true;
    jobIter++;
}

void quit()
{
    printf("\n");
    run = false;
    killall(jobArr, &jobIter);
    return;
}

void loop(char home_dir[])
{
    historyInit();
    homeDir = home_dir;

    int exitCode = 0;
    getshPid();
    cdInit(home_dir);
    ctrlCZinit(home_dir);
    while (run)
    {
        //chk if anything ended..
        signal(SIGCHLD, bgEnded);

        if (!run )
            return;
        print_PS1(home_dir, exitCode);
        int lSize = getline(&line_read, &zero, stdin);
        // for ctrl-D
        if (lSize <= 0)
        {
            quit();
            break;
        }
        setChPid(0, NULL);

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
            if (!run)
                return;
            if (!pipeChk(listOfSemiSep[i]))
            {
                printf("NO PIPES HAHAH\n\n");
                exitCode = execCmd(listOfSemiSep[i], home_dir, jobArr, &jobIter, &kjobFlag);
            }
            else
                exitCode = Pipe(listOfSemiSep[i], home_dir, jobArr, &jobIter, &kjobFlag);
            if (!run)
                break;
            printf("!%d!\n", exitCode);
        }
        pushHisQ(toHis);
    }
}
