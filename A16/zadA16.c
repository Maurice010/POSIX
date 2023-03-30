#define _REENTRANT
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#define THREAD_NUM 2

// Dzielone zmienne:
int global_register = 0;
int kolej = 0;   // czyja kolej wejścia do sekcji krytycznej
bool flaga[2] = {false,false}; // chęć wejścia do sekcji kryt.


void *thread(void *arg)
{
	int j = *(int*)arg;
	int private_register;
	int k = 3;

	while(k>0)
	{
		flaga[j] = true;
		kolej = 1-j;
		while (flaga[1-j] == true && kolej == 1-j)
		{
			printf("");
		}  // czekaj
		
		//------------------Sekcja krytczna--------------
		private_register = global_register;
		private_register++;
		
		printf("Thread #%d is in critical section\n", j);
		sleep(2);
		
		global_register = private_register;
		//-----------------------------------------------
		
		flaga[j] = false;
		k--;
		// reszta
	}
	
	free(arg);
	return 0;
}

int main()
{
	int i;
	pthread_t threadID[THREAD_NUM];
	
	// Tworzenie watkow
	for(i = 0; i < THREAD_NUM; i++)
	{
		int* index = malloc(sizeof(int));
		*index = i;
		if(pthread_create(&threadID[i], NULL, &thread, index) != 0)
		{
			perror("pthread_create error");
			exit(1);
		}
	}
	
	for(i = 0; i < THREAD_NUM; i++)
	{
		// Nakazanie procesowi na czekanie na skonczenie watku
		if(pthread_join(threadID[i], NULL) != 0)
		{
			perror("pthread_join error");
			exit(2);
		}
	}
	printf("global_register = %d\n", global_register);
	
	
	return 0;
}
