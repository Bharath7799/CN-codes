#include <stdio.h>
#include <sys/types.h>
#include <poll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define shmkey 1234
#define shmsize 4

#define eerror(msg) { printf("%s\n", msg); exit(1); }
#define sfifo "fi.dat"
#define MAX 3

int init(int key)
{
	int shmid = shmget(key ,shmsize , IPC_CREAT|0666);
	if(shmid <=0)
	{
		printf("shmget error\n");
		exit(0);

	}
}

int tablecount=3;

void handler()
{
    printf("signal -- hii bro.\n");
    tablecount++;

}

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

   	int shmid= init(shmkey);
	int *ppid = (int *)shmat(shmid,NULL,0);
	*ppid = getpid();

     int fd3 = open(sfifo, 0666);
        if(fd3 == -1) eerror("sfifo error");
             int timeout_msecs = 500;
        printf("sfifo opened in read mode\n");

    while(1)
    {
    		printf("poll occured , tablecount : %d \n",tablecount );
    		signal(SIGUSR1,handler);
        if(tablecount>0)
       	{
	  	    read(fd3, buffer,128);
	    	printf("%s\n",buffer);
	    	
                str1=strtok(buffer," ");
                str2=strtok(NULL," ");
                printf("%s\n", str1 );
                printf("%s\n", str2 );

	        acceptReq(str1);
	        tablecount--;
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
}