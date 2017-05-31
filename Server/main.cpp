#include <stdio.h>
#include <stdlib.h>
#include "Epoll.h"

int main(int argc, char *argv[])
{
    if(argc!=2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    epoll_init(atoi(argv[1]));
}