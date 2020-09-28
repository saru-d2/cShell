#include "header.h"

pid_t shPid;
pid_t chPid = 0;
char *homeDir;

void getshPid()
{
    shPid = getpid();
}

void setChPid(int id)
{
    chPid = id;
}

void ctrlC(int nec)
{
    bool killChld = false;
    // printf("hullo\n");
    if (getpid() == shPid && chPid != 0){
        killChld = true;
        kill(chPid, SIGINT);
    }
    signal(SIGINT, ctrlC);
    if (!killChld)
    {
        printf("\n");
        print_PS1(homeDir);
    }
    fflush(stdout);
}

void ctrlZ()
{
    printf("hullo\n");
}

void ctrlCZinit(char *hDir)
{
    homeDir = hDir;
    signal(SIGINT, ctrlC);
    signal(SIGTSTP, ctrlZ);
}
