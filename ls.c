#include "header.h"

void assignPermissions(char permissions[], struct stat s)
{
    if (S_ISDIR(s.st_mode))
        strcat(permissions, "d");
    else
        strcat(permissions, "-");
    if (s.st_mode & S_IRUSR)
        strcat(permissions, "r");
    else
        strcat(permissions, "-");
    if (s.st_mode & S_IWUSR)
        strcat(permissions, "w");
    else
        strcat(permissions, "-");
    if (s.st_mode & S_IXUSR)
        strcat(permissions, "x");
    else
        strcat(permissions, "-");
    if (s.st_mode & S_IRGRP)
        strcat(permissions, "r");
    else
        strcat(permissions, "-");
    if (s.st_mode & S_IWGRP)
        strcat(permissions, "w");
    else
        strcat(permissions, "-");
    if (s.st_mode & S_IXGRP)
        strcat(permissions, "x");
    else
        strcat(permissions, "-");
    if (s.st_mode & S_IROTH)
        strcat(permissions, "r");
    else
        strcat(permissions, "-");
    if (s.st_mode & S_IWOTH)
        strcat(permissions, "w");
    else
        strcat(permissions, "-");
    if (s.st_mode & S_IXOTH)
        strcat(permissions, "x");
    else
        strcat(permissions, "-");
}

void ls(char *par[], int numPar, char home_dir[])
{
    bool a = false, l = false;
    bool takingFlags = true;
    char dir[100000];
    strcpy(dir, ".");
    for (int i = 0; i < numPar; i++)
    {

        if (takingFlags && strcmp(par[i], "-a") == 0)
            a = true;
        else if (takingFlags && strcmp(par[i], "-l") == 0)
            l = true;
        else if (takingFlags && strcmp(par[i], "-la") == 0 || strcmp(par[i], "-al") == 0)
            a = l = true;
        else
            strcpy(dir, par[i]);
    }
    printf("%s\n", dir);
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
    int numHardlinks, size;
    printf("%s %d\n", dir, cnt);
    char fName[100000];
    struct stat s;
    struct passwd *passUsr;
    struct group *grp;
    char permissions[100] = "", dateTime[50];
    for (int i = 0; i < cnt; i++)
    {
        strcpy(fName, dirs[i]->d_name);
        if (fName[0] == '.' && a == false)
            continue;
        stat(fName, &s);
        strcpy(permissions, "");
        // assign permissions..
        assignPermissions(permissions, s);
        numHardlinks = s.st_nlink;
        passUsr = getpwuid(s.st_uid);
        grp = getgrgid(s.st_gid);
        size = s.st_size;
        strftime(dateTime, 50, "%b %d %Y\t%H:%M", localtime(&(s.st_ctime)));
        if (l)
            printf("%s\t%d\t%s\t%s\t%d\t%s\t", permissions, numHardlinks, passUsr->pw_name, grp->gr_name, size, dateTime);
        printf("%s\n", fName);
    }
}