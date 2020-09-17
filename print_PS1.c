#include "header.h"

void print_PS1(char home_dir[])
{
    char user[10000], cwd[10000], hostName[10000];
    getlogin_r(user, sizeof(user));
    getcwd(cwd, sizeof(cwd));
    gethostname(hostName, sizeof(hostName));
    char addr[10000];
    strcpy(addr, "");
    if (strcmp(cwd, home_dir) == 0) // if its at "home"
        strcat(addr, "~");
    else
    {
        bool e = true;
        int hn = strlen(home_dir);
        int pn = strlen(cwd);
        char path[100000];
        strcpy(path, "");
        if (pn < hn)
            e = false;
        if (e)
            for (int i = 0; i < hn; i++)
                if (home_dir[i] != cwd[i])
                {
                    e = false;
                    break;
                }
        if (e)
        {
            strcat(path, "~");
            int ind = 1;
            for (int i = hn; i<pn; i++){
                path[ind++] = cwd[i];
            }
            path[ind] = '\0';
            strcat(addr, path);
        }
        else
        {
            strcat(addr, cwd);
        }
    }
    printf("<" TANGO_GREEN "%s@%s" TANGO_WHITE ":" TANGO_CYAN "%s" TANGO_WHITE "> ", user, hostName, addr);
}