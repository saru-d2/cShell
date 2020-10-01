#include "header.h"

pid_t shPid;
pid_t chPid = 0;
char *homeDir;
char *chName;
char blank[] = "";

void getshPid()
{
    shPid = getpid();
}

void setChPid(int id, char *cmd)
{
    // printf("@%d %s@\n", id, cmd);
    chPid = id;
    
    chName = cmd;
    if(chName == NULL)
    chName = blank;
}

void ctrlC(int nec)
{
    bool killChld = false;
    // printf("hullo\n");
    if (getpid() == shPid && chPid != 0)
    {
        killChld = true;
        kill(chPid, SIGINT);
    }
    signal(SIGINT, ctrlC);
    if (getpid() == shPid)
    {
        printf("\n");
        print_PS1(homeDir, 0);
    }
    fflush(stdout);
}

void ctrlZ(int nec)
{
    // printf("hullo\n");
    if (getpid() != shPid)
        return;
    if (chPid != 0)
    {
        kill(chPid, SIGTTIN);
        kill(chPid, SIGTSTP);
        printf("?%s?", chName);
        addToJobArr(chPid, chName);
        printf("wow\n");
        fflush(NULL);
    }
    signal(SIGTSTP, ctrlZ);
 if (getpid() == shPid)
    {
    }
    return;
}

void ctrlCZinit(char *hDir)
{
    homeDir = hDir;
    signal(SIGINT, ctrlC);
    signal(SIGTSTP, ctrlZ);
}
