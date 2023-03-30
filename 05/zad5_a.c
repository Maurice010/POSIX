#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

void cleanup()
{
	if(unlink("towarfifo") == -1)
	{
		perror("FIFO delete error");
	}
	else printf("Usuniecie towarfifo\n");
}

int main()
{
    int fdfifow;
    int fdtowar;
    char towarP[3];
    
    if(mkfifo("towarfifo", 0644) == -1)
    {
    	perror("fifo error");
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
		int fdfifor;
		
		srand(time(NULL));
		
		printf("Otwarcie pliku magazyn.txt\n");
		fdmagazyn = open("magazyn.txt", O_WRONLY);
		if(fdmagazyn == -1)
		{
			perror("open magazyn.txt error");
			_exit(4);
		}
		
		fdfifor = open("towarfifo", O_RDONLY);
		if(fdfifor == -1)
		{
			perror("open towarfifo error");
			_exit(3);
		}
		
		while(1)
		{
			sleep(rand()%4 + 1);
			
			if(read(fdfifor, towarK, 2) > 0)
			{
			write(STDOUT_FILENO, "Konsument pobral: ", strlen("Konsument pobral: "));
			write(STDOUT_FILENO, towarK, strlen(towarK));
			write(STDOUT_FILENO, "\n", strlen("\n"));
			write(fdmagazyn, towarK, strlen(towarK));
			}
			else break;
		}
		
		printf("Zapisywanie do magazyn.txt zakonczone\n");
		
		close(fdfifor);
		close(fdmagazyn);

		_exit(EXIT_SUCCESS);
		break;
	default:
    		srand(time(NULL));
    		
    		printf("Otwarcie pliku towar.txt\n");
    		
		fdtowar = open("towar.txt", O_RDONLY);
		if(fdtowar == -1)
		{
			perror("open towar.txt error");
			exit(5);
		}
		
		printf("Otwarcie pliku towarfifo\n");
		
		fdfifow = open("towarfifo", O_WRONLY);
		if(fdfifow == -1)
		{
			perror("open towarfifo error");
			exit(6);
		}
		
		printf("Zapisywanie...\n");
		
		while(read(fdtowar, towarP, 3) > 0)
		{
			sleep(rand()%2 + 1);
			
			write(STDOUT_FILENO, "Producent wyprodukowal: ", strlen("Producent wyprodukowal: "));
			write(STDOUT_FILENO, towarP, strlen(towarP));
			write(STDOUT_FILENO, "\n", strlen("\n"));
			write(fdfifow, towarP, strlen(towarP));
		}
		
		close(fdtowar);
		close(fdfifow);
		
		wait(NULL);
		atexit(cleanup);
		break;
    }

    return 0;
}
