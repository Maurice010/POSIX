#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fdpipe[2];
    int fdtowar;
    char towarP[3];
    
    if(pipe(fdpipe) == -1)
    {
    	perror("pipe error");
    	exit(1);
    }
    
    switch(fork())
    {
	case -1:
		perror("fork error");
		exit(2);
	case 0: ;
		char towarK[2];
		int fdmagazyn;
		
		close(fdpipe[1]);
		
		srand(time(NULL));
		
		printf("Otwarcie pliku magazyn.txt\n");
		fdmagazyn = open("magazyn.txt", O_WRONLY);
		if(fdmagazyn == -1)
		{
			perror("open magazyn.txt error");
			exit(3);
		}
		
		while(read(fdpipe[0], towarK, 2) > 0)
		{
			sleep(rand()%4 + 1);
			
			write(STDOUT_FILENO, "Konsument pobral: ", strlen("Konsument pobral: "));
			write(STDOUT_FILENO, towarK, strlen(towarK));
			write(STDOUT_FILENO, "\n", strlen("\n"));
			write(fdmagazyn, towarK, strlen(towarK));
		}
		
		close(fdpipe[0]);
		close(fdmagazyn);
		_exit(EXIT_SUCCESS);
		break;
	default:
    		close(fdpipe[0]);

    		printf("Otwarcie pliku towar.txt\n");
		fdtowar = open("towar.txt", O_RDONLY);
		if(fdtowar == -1)
		{
			perror("open towar.txt error");
			exit(4);
		}

		while(read(fdtowar, towarP, 3) > 0)
		{
			sleep(rand()%2 + 1);
			
			write(STDOUT_FILENO, "Producent wyprodukowal: ", strlen("Producent wyprodukowal: "));
			write(STDOUT_FILENO, towarP, strlen(towarP));
			write(STDOUT_FILENO, "\n", strlen("\n"));
			write(fdpipe[1], towarP, strlen(towarP));
		}
		
		close(fdpipe[1]);
		close(fdtowar);
		
		wait(NULL);
		break;
    }
    
    return 0;
}
