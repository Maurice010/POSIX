#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void my_sighandler(int sig)
{
    printf("Przechwycenie i wlasna obsluga sygnalu %d\n", sig);
}

int main(int argc, char* argv[])
{
    int sig, opcja;
    printf("UID = %d, GID = %d, PID = %d, PPID = %d, PGID = %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
    if(argc != 3)
    {
        printf("Nieodpowiednia ilosc argumentow -> ./zad3 [numer sygnalu] [opcja]\n");
        exit(EXIT_FAILURE);
    }
    sscanf(argv[1], "%d", &sig);
    sscanf(argv[2], "%d", &opcja);
    printf("Opcja: %d\n", opcja);
    printf("Sygnal: %d\n", sig);
    
    switch(opcja)
    {
        case 1:
            if(signal(sig, SIG_DFL) == SIG_ERR)
            {
                perror("Funkcja signal ma problem");
                exit(EXIT_FAILURE);
            }
            printf("Wykonanie operacji domyslnej dla sygnalu %d\n", sig);
            break;
        case 2:
            if(signal(sig, SIG_IGN) == SIG_ERR)
            {
                perror("Funkcja signal ma problem");
                exit(EXIT_FAILURE);
            }
            printf("Ignorowanie sygnalu %d\n", sig);
            break;
        case 3:
            if(signal(sig, my_sighandler) == SIG_ERR)
            {
                perror("Funkcja signal ma problem");
                exit(EXIT_FAILURE);
            }
            break;
        default:
            printf("Nieprawidlowa wartosc zmiennej opcja\n");
            exit(EXIT_FAILURE);
            break;
    }
    pause();
    
    return 0;
}
