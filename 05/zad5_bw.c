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
    int fdfifow;
    int fdtowar;
    char towarP[3];
    
    srand(time(NULL));
    
    printf("Otwarcie pliku towar.txt\n");
    
    fdtowar = open("towar.txt", O_RDONLY);
    if(fdtowar == -1)
    {
    	perror("open towar.txt error");
    	exit(1);
    }
    
    printf("Otwarcie pliku towarfifo\n");
    
    fdfifow = open("towarfifo", O_WRONLY);
    if(fdfifow == -1)
    {
    	perror("open towarfifo error");
    	exit(2);
    }
    
    printf("Zapisywanie do towarfifo\n");
    
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
    
    return 0;
}
