#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/* proces adoptujacy osierocone procesy - systemd PID = 984 */

int main(){
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
                sleep(1);
                printf("UID = %d, GID = %d, PID = %d, PPID = %d, PGID = %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
        }
    }
    return 0;
}
