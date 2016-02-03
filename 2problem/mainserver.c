#include <stdio.h>
#include <sys/types.h>
#include <poll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define eerror(msg) { printf("%s\n", msg); exit(1); }
#define sfifo "fi.dat"
#define MAX 3


//struct pollfd fdsf[1];
int fd[MAX]; int fd2[MAX];
int nClient=1;
char buffer[128], tmp[128];
char *str1;
char *str2;

void acceptReq(const char arg[])
{
     printf("Got a req %s\n",arg);
     strcpy(tmp, arg);
     strcat(tmp, "r");
     printf("%s\n",tmp );
     sleep(2);
     fd[nClient-1] = open(tmp, O_WRONLY);
     if(fd[nClient-1] == -1) eerror("WERROR!!!");
     
     strcpy(tmp, arg);
     strcat(tmp, "w");
     printf("%s\n",tmp );
     fd2[nClient-1] = open(tmp, O_RDONLY);
     if(fd2[nClient-1]== -1) eerror("RERROR!!!");
     nClient++;
     printf("Req success %d\n", nClient);
 }


int main()
{
	printf("this is main server\n");
   mkfifo(sfifo, 0666); int i,j;


     int fd3 = open(sfifo, 0666);
        if(fd3 == -1) eerror("sfifo error");
             int timeout_msecs = 500;
        printf("sfifo opened in read mode\n");

    while(1)
    {
    		printf("poll occured\n" );
     
	  	read(fd3, buffer,128);
	    	printf("%s\n",buffer);
	    	
                str1=strtok(buffer," ");
                str2=strtok(NULL," ");
                printf("%s\n", str1 );
                printf("%s\n", str2 );

	        acceptReq(str1);
	        printf("i am still in main server\n" );
	         
	        if(fork() == 0)	
	        {
	        	printf("iam child of main server 2\n" );
	        	char b[128];
	        	strcpy(b,"./");
	        	strcat(b,str2);
	        	strcat(b,"\0");
	        	printf("%s\n",b );
	        	
	        	dup2(fd[nClient-2], 1);
	        	dup2(fd2[nClient-2], 0);
	        		execlp(b,b,NULL);
	        	printf("execlp error\n" );
        	}

    }
}