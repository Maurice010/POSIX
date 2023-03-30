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
    char towarK[2];
    int fdmagazyn;
    int fdfifor;
    
    srand(time(NULL));
    
    printf("Otwarcie pliku magazyn.txt\n");
    fdmagazyn = open("magazyn.txt", O_WRONLY);
    if(fdmagazyn == -1)
    {
    	perror("open magazyn.txt error");
    	exit(3);
    }
    
    fdfifor = open("towarfifo", O_RDONLY);
    if(fdfifor == -1)
    {
    	perror("open towarfifo error");
    	exit(4);
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

    return 0;
}
