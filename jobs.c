#include "header.h"
#include "JobStruct.h"

void jobs(int numPar, char *par[], job jobArr[], int *jobIterPtr)
{
    int jobCnt = *jobIterPtr;
    for (int i = 0; i < jobCnt; i++)
    {
        bool run;
        if (!jobArr[i].running)
            continue;
        int pid = jobArr[i].id;
        char procFile[1000];
        sprintf(procFile, "/proc/%d/stat", pid);
        FILE *fd = fopen(procFile, "r");
        if (fd == NULL)
            run = false;
        else
        {
            char infoStr[1000];
            for (int i = 0; fscanf(fd, "%s", infoStr); i++)
            {
                if (i == 3)
                    break;
                if (i == 2)
                {
                    // printf("Process Status -- %s\n", infoStr);
                    if (strcmp("T", infoStr) == 0)
                    {
                        run = false;
                    }
                    else
                        run = true;
                }
            }
        }

        printf("[%d] ", i +1);
        if (run)printf("Running ");
        else printf("Stopped ");
        printf("%s [%d]\n", jobArr[i].name, jobArr[i].id + 1);

    }
}