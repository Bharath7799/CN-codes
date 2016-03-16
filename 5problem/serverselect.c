#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <poll.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/time.h>


#define ssfifo "file1.dat"
#define shmkey 1234
#define shmsize 4

int ofd;
int fd2[3],fd1[3]; int nClient=0,val;
char mbuf[1024];

void handler()
{
	printf("signal -- hii bro.\n");
	write(ofd,mbuf,1024);
}
void mainsave(char *bu)
{
	printf(" this is in msave : %s\n",bu );
	strcat(mbuf,bu);
}
int init(int key)
{
	int shmid = shmget(key ,shmsize , IPC_CREAT|0666);
	if(shmid <=0)
	{
		printf("shmget error\n");
		exit(0);

	}
}
int main(int argc, char const *argv[])
{
	
	int shmid= init(shmkey);
	int *ppid = (int *)shmat(shmid,NULL,0);
	*ppid = getpid();
	
	//pipe declaration;
	int pfd[2];
	//fifo declaration;
	int ffd;
	pipe(pfd);
	mkfifo("ssfifo",0666);
	ffd=open("ssfifo", 0666);

	printf("pipe and fifo are created\n");
	fd_set readset;
    int maxfd;
	//struct pollfd fds[4];
	fd1[0]=pfd[0];
	fd1[1]=ffd;


	mkfifo("out.dat",0666);
	ofd=open("out.dat",0666);
	printf("output file is created\n");
	FILE *fp;
	//int status;
	char path[128];
	fp = popen("./sopen", "r");
	printf("popen started \n");
	if (fp == NULL)
	{
		printf("error in popen creation\n");
	}
	fd1[2]=fileno(fp);

	//fd1[3]=0;
	printf("hii im before poll\n");
	int i,j;

	printf("hii im after poll\n");

	int pid=fork();
	printf("pid : %d\n",pid );
	if(pid == 0)
	{  
		sleep(2);
		{
			close(pfd[0]);
			printf("hii im child process\n");

			char buf[128];
			sprintf(buf,"hii im child");
			write(pfd[1], buf, 128);
			close(pfd[1]);
           //  sleep(2);
		}
	}
	else 
	{
		close(pfd[1]);
		printf("hii im in main process\n");
		int i=-1;
		while(1)
		{
			FD_ZERO(&readset);
		      maxfd=0;
		     for (j=0; j<3; j++)
		      {
		           FD_SET(fd1[j], &readset);
		           maxfd = (maxfd>fd1[j])?maxfd:fd1[j];
		       }
		    //   FD_CLR(fd1[2],&readset);
			signal(SIGUSR1,handler);
		//	for (;;);
			
			int ret=select(maxfd+1,&readset,NULL,NULL,NULL);
			if(ret>0)
			{
				//printf("poll occured : ");
				sleep(1);
				for (i = 0; i < 3; ++i)
				{
					if(FD_ISSET(fd1[i], &readset))
					{

						//printf("%d\n", i );
						char buf[128];
						 memset(buf,'\0',128);
						int size=read(fd1[i],buf,128);
						if(size<=0) ;
						else 
							{printf("%s\n",buf );
						mainsave(buf);
					}

					}
					// if (i==2)
					// {
					// 	//pclose(fp);
					// 	FD_CLR(fd1[2],&readset);
					// }
				}
			}
		}
	}
	
	return 0;
}
