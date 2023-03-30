#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mqueue.h>
#include <signal.h>
#include "zad8_lib.h"

mqd_t server_qd, client_qd;
char CLIENT_NAME[15];

void cleanup()
{
	printf("\nCleaning client %d...\n", getpid());

	// Zamkniecie kolejek
	if (mqclose(client_qd) == -1) {
		perror ("Client mq_close(/client) error");
		exit(6);
	}
	
	if (mqclose(server_qd) == -1) {
		perror ("Client mq_close(/server) error");
		exit(7);
	}
	
	// Usuniecie kolejki
	if (mqdelete(CLIENT_NAME) == -1) {
		perror ("Client mq_unlink error");
		exit(8);
	}
	printf("Client %d is closed\n", getpid());
	exit(0);
}

int main()
{
	struct mq_attr attr;
	// Sprawdzic rozmiary tablic i attr :P
	char solution[256];
	char equation[256];
	char to_solve[10];
	
	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 256;
	attr.mq_curmsgs = 0;
	
	//printf("%s\n", SERVER_NAME);
	
	if(signal(SIGINT, cleanup) == SIG_ERR)
	{
		perror("Signal error");
		exit(EXIT_FAILURE);
	}
	
	sprintf(CLIENT_NAME, "/%d", getpid());
	sprintf(equation, "%s ", CLIENT_NAME);

	printf("\n%s\n", CLIENT_NAME);
	// Otwarcie/stworzenie kolejki w trybie do odbierania wyniku z serwera
	if ((client_qd = mqcreate(CLIENT_NAME, O_RDONLY | O_CREAT, 0660, &attr)) == -1)
	{
		perror ("Client mq_open(/client) error");
		//exit (3);
	}
	
	// Otwarcie kolejki w trybie do nadawania do serwera, wrzucic nazwe z header
	if ((server_qd = mqopen(SERVER_NAME, O_WRONLY)) == -1)
	{
		perror ("Client mq_open(/server) error");
		//exit (4);
        }

	printf("Type equation in format int operator int: ");

	while(fgets(to_solve, 10, stdin))
	{
		sprintf(equation+strlen(CLIENT_NAME)+1, "%s", to_solve);
		// wyslanie zadania do serwera
		if(mqsend(server_qd, equation, strlen(equation) + 1, 0) == -1)
		{
		    perror("Client mq_send server error");
		}

		// odebranie rozwiazania z serwera 
		if(mqreceive(client_qd, solution, 256, NULL) == -1)
		{
		    perror("Client mq_receive error");
		    exit(5);
		}

		printf("Solution: %s\n", solution);
		
		memset(solution, 0, 256);

		printf("Type equation in format int operator int: ");
	}
	atexit(cleanup);
	
	return 0;
}
