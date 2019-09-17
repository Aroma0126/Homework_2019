

#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "unistd.h"


int main() {

    int i;
    if (fork())
    {
        i = wait();
        printf("It is parent process\n");
        printf("The child process,id number %d is finished\n",i);
    }
    else
    {
        printf("It is child process\n");
        sleep(10);
        exit(0);
    }
    return 0;
}