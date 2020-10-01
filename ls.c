#include "header.h"

void assignPermissions(char permissions[], struct stat s)
{
    S_ISDIR(s.st_mode) ? strcat(permissions, "d") : strcat(permissions, "-");
    s.st_mode &S_IRUSR ? strcat(permissions, "r") : strcat(permissions, "-");
    s.st_mode &S_IWUSR ? strcat(permissions, "w") : strcat(permissions, "-");
    s.st_mode &S_IXUSR ? strcat(permissions, "x") : strcat(permissions, "-");
    s.st_mode &S_IRGRP ? strcat(permissions, "r") : strcat(permissions, "-");
    s.st_mode &S_IWGRP ? strcat(permissions, "w") : strcat(permissions, "-");
    s.st_mode &S_IXGRP ? strcat(permissions, "x") : strcat(permissions, "-");
    s.st_mode &S_IROTH ? strcat(permissions, "r") : strcat(permissions, "-");
    s.st_mode &S_IWOTH ? strcat(permissions, "w") : strcat(permissions, "-");
    s.st_mode &S_IXOTH ? strcat(permissions, "x") : strcat(permissions, "-");
}

int ls(char *par[], int numPar, char home_dir[])
{
    bool a = false, l = false;
    char *dirList[10000], dot[] = ".";
    int dirNo = 0;
    for (int i = 0; i < numPar; i++)
    {

        if (strcmp(par[i], "-a") == 0)
            a = true;
        else if (strcmp(par[i], "-l") == 0)
            l = true;
        else if (strcmp(par[i], "-la") == 0 || strcmp(par[i], "-al") == 0)
            a = l = true;
        else
            dirList[dirNo++] = par[i];
    }
    if (dirNo == 0)
    {
        dirNo++;
        dirList[0] = dot;
    }
    for (int i = 0; i < dirNo; i++)
    {
        char *dir = dirList[i];
        if (dirNo > 1)
            printf("%s:\n", dir);
        if (dir[0] == '~')
        {
            char temp[100000];
            strcpy(temp, dir);
            strcpy(dir, home_dir);
            strcat(dir, temp + 1);
        }
        struct dirent **dirs;
        DIR *d;
        int cnt = scandir(dir, &dirs, NULL, alphasort);
        if (cnt < 0)
        {
            perror("ls");
            return -1;
        }
        int numHardlinks, size;
        char fName[100000];
        struct stat s;
        struct passwd *passUsr;
        struct group *grp;
        char permissions[100] = "", dateTime[50];
        int total = 0;
        for (int i =0; i<cnt; i++){
            strcpy(fName, dirs[i]->d_name);
            if (fName[0] == '.' && a == false)
                continue;
            char temp[100000];
            strcpy(temp, dir);
            strcat(temp, "/");
            strcat(temp, fName);
            stat(temp, &s);
            total += s.st_blocks;
        }
        if (l){
            printf("total: %d\n", total/2);
        }
        for (int i = 0; i < cnt; i++)
        {
            strcpy(fName, dirs[i]->d_name);
            if (fName[0] == '.' && a == false)
                continue;
            char temp[100000];
            strcpy(temp, dir);
            strcat(temp, "/");
            strcat(temp, fName);
            stat(temp, &s);
            strcpy(permissions, "");
            // assign permissions..
            assignPermissions(permissions, s);
            numHardlinks = s.st_nlink;
            passUsr = getpwuid(s.st_uid);
            grp = getgrgid(s.st_gid);
            size = s.st_size;
            strftime(dateTime, 50, "%b %d\t%H:%M", localtime(&(s.st_ctime)));
            
            if (l)
                printf("%s\t%d\t%s\t%s\t%d\t%s\t", permissions, numHardlinks, passUsr->pw_name, grp->gr_name, size, dateTime);
            printf("%s\n", fName);
        }
    }
    return 1;
}