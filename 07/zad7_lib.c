#include "zad7_lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>

// ############# SEMAFORY #############
sem_t *semaphore;

// TWORZENIE
sem_t *screate(const char *name, int oflag, mode_t mode, unsigned int value)
{
	semaphore = sem_open(name, oflag, mode, value);
	if(semaphore == SEM_FAILED)
	{
		perror("screate error");
		return semaphore;
	}
	else return semaphore;
}
// OTWIERANIE
sem_t *sopen(const char *name, int oflag)
{
	semaphore = sem_open(name, oflag);
	if(semaphore == SEM_FAILED)
	{
		perror("sopen error");
		return semaphore;
	}
	else return semaphore;
}
// UZYSKIWANIE WARTOSCI
int svalue(sem_t *sem, int *sval)
{
	if(sem_getvalue(sem, sval) == -1)
	{
		perror("svalue error");
		return -1;
	}
	else return 0;
}
// OPEROWANIE
// operacja podnoszenia V(s)
int sup(sem_t *sem)
{
	if(sem_post(sem) == -1)
	{
		perror("sup error");
		return -1;
	}
	else return 0;
}
// operacja opuszczania P(s)
int sdown(sem_t *sem)
{
	if(sem_wait(sem) == -1)
	{
		perror("sdown error");
		return -1;
	}
	else return 0;
}
// ZAMYKANIE
int sclose(sem_t *sem)
{
	if(sem_close(sem) == -1)
	{
		perror("sdown error");
		return -1;
	}
	else return 0;
}
// USUWANIE
int sdelete(const char *name)
{
	if(sem_unlink(name) == -1)
	{
		perror("sdelete error");
		return -1;
	}
	else return 0;
}

// ############# PAMIEC_DZIELONA #############
int shm_fd;

// USUWANIE
int shdelete(const char *name)
{
	if(shm_unlink(name) == -1)
	{
		perror("shdelete error");
		return -1;
	}
	else return 0;
}
// TWORZENIE/OTWIERANIE
int shopen(const char *name, int flags, mode_t mode)
{
	shm_fd = shm_open(name, flags, mode);
	if(shm_fd == -1)
	{
		perror("shopen error");
		return -1;
	}
	else return shm_fd;
}
// USTAWIANIE ROZMIARU
int shsize(int fd, off_t length)
{
	if(ftruncate(fd, length) == -1)
	{
		perror("shsize error");
		return -1;
	}
	else return 0;
}
// ODWZOROWANIE PAMIECI DZIELONEJ
void *shmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	return mmap(addr, length, prot, flags, fd, offset);
}
// USUNIECIE ODWZOROWANIA PAMIECI DZIELONEJ
int delshmap(void *addr, size_t length)
{
	if(munmap(addr, length) == -1)
	{
		perror("delshmap error");
		return -1;
	}
	else return 0;
}
// ZAMYKANIE
int shclose(int fd)
{
	if(close(fd) == -1)
	{
		perror("shclose error");
		return -1;
	}
	else return 0;
}
