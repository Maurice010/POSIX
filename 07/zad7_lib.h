#ifndef _ZAD7_LIB_
#define _ZAD7_LIB_

#include <semaphore.h>

extern sem_t *semaphore;
sem_t *screate(const char *name, int oflag, mode_t mode, unsigned int value);
sem_t *sopen(const char *name, int oflag);
int svalue(sem_t *sem, int *sval);
int sup(sem_t *sem);
int sdown(sem_t *sem);
int sclose(sem_t *sem);
int sdelete(const char *name);

int shdelete(const char *name);
int shopen(const char *name, int flags, mode_t mode);
int shsize(int fd, off_t length);
void *shmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int delshmap(void *addr, size_t length);
int shclose(int fd);
#endif
