#include "header.h"

void print_PS1(char home_dir[])
{
    char user[100000], cwd[100000], hostName[100000];
    getlogin_r(user, sizeof(user));
    getcwd(cwd, sizeof(cwd));
    gethostname(hostName, sizeof(hostName));
    char ret[300000];
    strcpy(ret, "<");
    strcat(ret, user);
    strcat(ret, "@");
    strcat(ret, hostName);
    strcat(ret, ":");
    if (strcmp(cwd, home_dir) == 0) // if its at "home"
        strcat(ret, "~");
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
            strcat(ret, path);
        }
        else
        {
            strcat(ret, cwd);
        }
    }
    strcat(ret, ">");
    ret[strlen(ret)] = '\0';
    printf("%s", ret);
}