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

void printCharArray(char *arr, size_t len)
{
    printf("arr: ");
    for (size_t i = 0; i < len; ++i) {
        printf("%c, ", arr[i]);
    }
    printf("\n");
}

void cleanup()
{
	printf("\nCleaning server...\n");
	// Zamkniecie kolejek
	if(mqclose(client_qd) == -1)
	{
		perror ("Client mq_close error");
		exit (9);
	}
	
	if(mqclose(server_qd) == -1)
	{
		perror ("Client mq_close error");
		exit (10);
	}
	
	// Usuniecie kolejki
	if(mqdelete(SERVER_NAME) == -1)
	{
		perror ("Client mq_unlink error");
		exit (11);
	}
	
	printf("Server is closed\n");
	exit(0);
}

int main()
{
	struct mq_attr attr;
	char recived[256];
	char CLIENT_NAME[256];
	char solution[256];
	char operation;
	int left, right;
	int int_solution;
	
	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 256;
	attr.mq_curmsgs = 0;
	
	if(signal(SIGINT, cleanup) == SIG_ERR)
	{
		perror("Funkcja signal ma problem");
		exit(EXIT_FAILURE);
	}
	
	// Z tej kolejki serwer odbiera info od klienta, sprawdzic 0660
	if((server_qd = mqcreate(SERVER_NAME, O_RDONLY | O_CREAT, 0660, &attr)) == -1)
	{
		perror("Server mq_open(/server) error");
		exit(1);
	}

	while(1)
	{
		// odebranie wiadomosci od klienta
		if(mqreceive(server_qd, recived, 256, NULL) == -1)
		{
		    perror("Server mq_receive error");
		    exit(2);
		}

		sscanf(recived, "%s %d %c %d" , CLIENT_NAME, &left, &operation, &right);
		
		printf ("Server request to solve %d %c %d from %s\n", left, operation, right, CLIENT_NAME);

		// otwarcie kolejki klienta do wyslania rozwiazania
		if((client_qd = mqopen(CLIENT_NAME, O_WRONLY)) == 1)
		{
		    perror("Server mq_open(/client) error");
		}
		
		// wykonanie dzialania i zapisanie w solution
		switch(operation)
		{
			case '+':
				int_solution = left+right;
				break;
			case '-':
				int_solution = left-right;
				break;
			case '*':
				int_solution = left*right;
				break;
			case '/':
				int_solution = left/right;
				break;
		}
		sprintf(solution, "%d", int_solution);
		
		// wyslanie rozwiazania do klienta
		if(mqsend(client_qd, solution, strlen(solution), 0) == -1)
		{
		    perror("Server mq_send(client) error");
		}

		printf("Server solution sent to %s\n", CLIENT_NAME);
		memset(solution, 0, 256);
	}
	atexit(cleanup);
	
	return 0;
}
