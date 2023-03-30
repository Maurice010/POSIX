#define _POSIX_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    int sig, id;
    
    sscanf(argv[1], "%d", &sig);
    id = fork();
    
    switch(id)
    {
        case -1:
            perror("fork error");
            exit(1);
            break;
        case 0:
            execlp("./zad3_a.x", "zad3_a.x", argv[1], argv[2], NULL);
            perror("execlp error");
            _exit(2);
            break;
        default:
            if(kill(id, 0) == -1)
            {
                perror("kill error");
            }
            else
            {
                printf("Wysłanie sygnału %d do %d\n", sig, id);
                /* Przed zastosowaniem sleep najprawdobodobniej proces macierzysty
                szybciej dochodzil do default i usuwal proces potomny zanim ten
                wywolywal funkcje execlp */
                sleep(1);
                kill(id, sig);
            }
            break;
    }

    wait(NULL);
    return 0;
}
