#include "header.h"
#include "JobStruct.h"

void overkill(int numPar, char *par[], job jobArr[], int *jobCnt)
{
    if (numPar != 0)
    {
        printf("Wrong no. of arguments");
        return;
    }
    killall(jobArr, jobCnt);
}

void killall(job jobArr[], int *jobCnt){
    for (int i =0; i<*jobCnt; i++){
        kill(jobArr[i].id, 9);
    }
    *jobCnt = 0;
}