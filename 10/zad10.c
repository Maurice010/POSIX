#define _REENTRANT
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#define THREAD_NUM 4

// Dzielone zmienne:
bool wybieranie[THREAD_NUM];   //-> wszystkie zainicjowane na: false 
int numer[THREAD_NUM];         //-> wszystkie zainicjowane na: 0
int global_register = 0;

void *thread(void *arg)
{
	int thread_index = *(int*)arg;
	int i, j, max_num, private_register;

	// Przypisywanie numeru
	wybieranie[thread_index] = true;
	
	max_num = 0;
	for(i = 0; i < THREAD_NUM; i++)
	{
		if(max_num < numer[i])
		{
			max_num = numer[i];
		}
	}
	
	numer[thread_index] = max_num + 1;
	wybieranie[thread_index] = false;
	
	// Wejscie
	for(j = 0; j < THREAD_NUM; j++)
	{
		while(wybieranie[j]); // czekaj
		while(numer[j] != 0 && 
			(numer[j] < numer[thread_index] || (numer[j] == numer[thread_index]
			&& j < thread_index)))
		{
			printf("");
		} // czekaj
	}

	//------------------Sekcja krytczna--------------
	private_register = global_register;
	private_register++;
	
	printf("Thread #%d is in critical section\n", thread_index);
	sleep(2);
	
	global_register = private_register;
	//-----------------------------------------------

	numer[thread_index] = 0;

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
