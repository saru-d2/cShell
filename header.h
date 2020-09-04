#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <pwd.h>
#include <fcntl.h>
#include <time.h>
#include <grp.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef struct job
{
    int id;
    char *name;
} job;


void loop();      //main loop..
void print_PS1(); //print the PS1..
void cd();
void pwd();
void echo();
void ls();
void assignPermissions();
void foregnd();
void backgnd();
void clear();
void pinfo();
int strToNum();