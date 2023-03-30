#define _POSIX_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void child_process(char* argv1, char* argv2);

int main(int argc, char *argv[])
{
    int sig, id, i, statloc, loc;
    char* argv1 = argv[1];
    char* argv2 = argv[2];
    
    printf("Proces macierzysty: %d %d\n", getpid(), getpgid(0));
    sscanf(argv[1], "%d", &sig);
    /* Utworzenie procesu potomnego */
    id = fork();
    
    switch(id)
    {
        case -1:
            perror("fork error");
            exit(1);
            break;
        case 0:
            /* Mianowanie nowo utworzonego procesu liderem grupy */
            setpgid(id, 0);
            printf("Proces potomny: %d %d\n", getpid(), getpgid(0));
            /* Uruchomienie w nim procesow potomnych */
            child_process(argv1, argv2);
            child_process(argv1, argv2);
            child_process(argv1, argv2);
            if(signal(sig, SIG_IGN) == SIG_ERR)
            {
                perror("Funkcja signal ma problem");
                exit(EXIT_FAILURE);
            }
            for(i=0; i<3; i++)
            {
                loc = wait(&statloc);
                printf("#%d %d\n", i, loc);
            }

            break;
        default:
            id = (-1)*id;
            sleep(5);
            if(kill(id, 0) == -1)
            {
                perror("kill error");
            }
            else
            {
                printf("Wysłanie sygnału %d do %d\n", sig, id);
                kill(id, sig);
            }
            break;
    }

    wait(NULL);
    return 0;
}

void child_process(char* argv1, char* argv2)
{
    switch(fork())
    {
        case -1:
            perror("fork error");
            exit(1);
            break;
        case 0:
            execlp("./zad3_a.x", "zad3_a.x", argv1, argv2, NULL);
            perror("execlp error");
            _exit(2);
            break;
    }
}
