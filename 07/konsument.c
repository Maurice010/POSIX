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
	char bufor[NBUF][NELE]; // Wspolny bufor danych
	int wstaw, wyjmij, stop, count; // Pozycje wstawiania i wyjmowania z bufora
} SegmentPD;

int main()
{
	int shm_fd;
	int fdtowar;
	sem_t *semaphore_PROD;
	sem_t *semaphore_KONS;
	
	// Otwarcie pamieci dzielonej
	shm_fd = shopen("/shm", O_RDWR, 0);
	SegmentPD *wpd = (SegmentPD *) shmap(NULL, sizeof(SegmentPD), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	
	// Otwarcie pliku txt
	fdtowar = open("magazyn.txt", O_WRONLY);
	if(fdtowar == -1)
	{
		perror("open magazyn.txt error");
		exit(1);
	}
	
	// Otwarcie semaforow
	semaphore_PROD = sopen("/semaphore_PROD", 0);
	semaphore_KONS = sopen("/semaphore_KONS", 0);
	
	// Produkcja towaru
	while (1) {
		// Opusc semafor Konsumenta
		if(sdown(semaphore_KONS) == -1)
		{
			sclose(semaphore_PROD);
			sclose(semaphore_KONS);
			exit(2);
		}

		if(write(fdtowar, wpd->bufor[wpd->wyjmij], 3) > 0)
		{
			printf("Konsument pobral <%s> z bufor[%d]\n\n", wpd->bufor[wpd->wyjmij], wpd->wyjmij);
			wpd->count = wpd->count - 1;

		}
		if(wpd->stop == 1 && wpd->count == 0)
		{
			break;
		}
		wpd->wyjmij = (wpd->wyjmij + 1) % NBUF; // Przesun pozycje wstawiania o 1 dalej
		// Podniesc semafor Producenta
		if(sup(semaphore_PROD) == -1)
		{
			sclose(semaphore_KONS);
			sclose(semaphore_PROD);
			exit(3);
		}
	}

	// Zamkniecie pliku txt
	close(fdtowar);

	// Zamkniecie semaforow
	sclose(semaphore_PROD);
	sclose(semaphore_KONS);
	
	// Zamkniecie pamieci dzielonej
	delshmap(wpd, sizeof(SegmentPD));
	shclose(shm_fd);
	
	return 0;
}
