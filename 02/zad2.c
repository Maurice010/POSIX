#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int i;
    printf("Proces macierzysty:\n");
    printf("UID = %d, GID = %d, PID = %d, PPID = %d, PGID = %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
    printf("Procesy potomne:\n");
    for(i=0; i<3; i++)
    {
        switch(fork())
        {
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                execlp(argv[1], "zad2_a.x", NULL);
                perror("execlp error");
                _exit(2);
        }
    }
    for(i=0; i<3; i++)
    {
    	wait(NULL);
    }
    return 0;
}
