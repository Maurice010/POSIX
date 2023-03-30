#define _REENTRANT
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


pthread_mutex_t mutex;
int global_register = 0;

void gotoxy(unsigned x, unsigned y)
{
  printf("\033[%d;%dH\033[2K", y, x);
}

void* hello(void* arg)
{
	int thread_index = *(int*)arg;
	int i;
	int private_register;
	
	for(i = 0; i < 3; i++)
	{
		
		printf("Thread #%d is in private section\n", thread_index);
		printf("\033[2K");
		
		//------------------Sekcja krytczna--------------
		pthread_mutex_lock(&mutex);
		//printf("\033[2K");
		
		private_register = global_register;
		private_register++;
		
		gotoxy(60,0);
		printf("Thread #%d is in critical section\n", thread_index);
		printf("\033[2K");
		
		sleep(2);
		
		global_register = private_register;
		pthread_mutex_unlock(&mutex);
		//-----------------------------------------------
	}
	free(arg);
}

int main()
{
	pthread_t threadID[3];
	int i;
	
	pthread_mutex_init(&mutex, NULL);
	
	// Wyczysc ekran
	if (system("clear") == -1)
	{
		perror("Error in call to system() function");
		exit(EXIT_FAILURE);
	}
	
	// Creating multiple threads
	for(i = 0; i < 3; i++)
	{
		int* index = malloc(sizeof(int));
		*index = i;
		if(pthread_create(&threadID[i], NULL, &hello, index) != 0)
		{
			perror("pthread_create error");
			exit(1);
		}
	}
	for(i = 0; i < 3; i++)
	{
		// Nakazanie procesowi na czekanie na skonczenie watku
		if(pthread_join(threadID[i], NULL) != 0)
		{
			perror("pthread_join error");
			exit(2);
		}
	}

	sleep(2);
	if (system("clear") == -1)
	{
		perror("Error in call to system() function");
		exit(EXIT_FAILURE);
	}
	printf("global_register = %d\n", global_register);
	pthread_mutex_destroy(&mutex);
	
	return 0;
}
