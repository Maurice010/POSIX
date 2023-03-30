#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <signal.h>
#include "zad7_lib.h"

#define NELE 20 // Rozmiar elementu bufora (jednostki towaru) w bajtach
#define NBUF 5 // Liczba elementow bufora

// Segment pamieci dzielonej
typedef struct {
	// Wspolny bufor danych
	char bufor[NBUF][NELE];
	
	// Pozycje wstawiania i wyjmowania z bufora
	int wstaw, wyjmij, stop, count;
} SegmentPD;

// Czyszczenie
void cleanup()
{
	// Usuniecie semaforow
	if(sdelete("/semaphore_PROD") == 0)
	{
		printf("Usuniecie semaphore_PROD\n");
	}
	
	if(sdelete("/semaphore_KONS") == 0)
	{
		printf("Usuniecie semaphore_KONS\n");
	}
	
	// Czyszczenie pamieci dzielonej
	if(shdelete("/shm") == 0)
	{
		printf("Usuniecie pamieci dzielonej\n");
	}
}

int main()
{
	int shm_fd;
	int i;
	sem_t *semaphore_PROD;
	sem_t *semaphore_KONS;
		
	// Utworzenie pamieci dzielonej
	shm_fd = shopen("/shm", O_CREAT | O_RDWR, 0666);
	shsize(shm_fd, sizeof(SegmentPD));
	// Tworzenie bufora cyklicznego, chyba tutaj jest niepotrzebne, wstarczy zrobic w konusmencie i producencie
	SegmentPD *wpd = (SegmentPD *) shmap(NULL, sizeof(SegmentPD), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	
	wpd->wyjmij = 0;
	wpd->wstaw = 0;
	wpd->stop = 0;
	wpd->count = 0;
	
	// Utworzenie semaforow
	semaphore_PROD = screate("/semaphore_PROD", O_CREAT, 0644, 5); // Semafor do wstrzymywania Producenta
	semaphore_KONS = screate("/semaphore_KONS", O_CREAT, 0644, 0); // Semafor do wstrzymywania Konsumenta
	
	
	// Utworzenie procesow producenta i konsumenta
	switch(fork())
	{
		case -1:
			perror("fork error");
			exit(2);
		case 0:
			execlp("./producent.x", "producent.x", NULL);
			perror("execlp error");
			_exit(3);
	}
	
	switch(fork())
	{
		case -1:
			perror("fork error");
			exit(4);
		case 0:
			execlp("./konsument.x", "konsument.x", NULL);
			perror("execlp error");
			_exit(5);
	}
	// Czekanie na zakonczenie procesow
	for(i=0; i<2; i++)
	{
		wait(NULL);
	}
	
	// Zamkniecie semaforow
	sclose(semaphore_PROD);
	sclose(semaphore_KONS);
	
	// Zamkniecie pamieci dzielonej
	delshmap(wpd, sizeof(SegmentPD));
	shclose(shm_fd);

	// Czyszczenie
	if(signal(SIGINT, cleanup) == SIG_ERR)
	{
		perror("Funkcja signal ma problem");
		exit(EXIT_FAILURE);
	}

        
	atexit(cleanup);
	
	
	return 0;
}
