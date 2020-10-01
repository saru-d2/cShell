#include "header.h"

int clear(){
    printf("\e[1;1H\e[2J");
    return 1;
}