#include "header.h"

int main(int argc, char *argv[]){
    char home_dir[100000];
    getcwd(home_dir, sizeof(home_dir));
    loop(home_dir);
    return 0;
}