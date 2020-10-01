#include "header.h"
#include "JobStruct.h"

int overkill(int numPar, char *par[], job jobArr[], int *jobCnt)
{
    if (numPar != 0)
    {
        printf("Wrong no. of arguments");
        return -1;
    }
    return killall(jobArr, jobCnt);
}

int killall(job jobArr[], int *jobCnt){
    for (int i =0; i<*jobCnt; i++){
        kill(jobArr[i].id, 9);
    }
    *jobCnt = 0;
    return 1;
}