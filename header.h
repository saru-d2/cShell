#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <dirent.h>
#include <sys/wait.h>

void loop();      //main loop..
void print_PS1(); //print the PS1..
void cd();
void pwd();
void echo();
void ls();
void assignPermissions();
void foregnd();
