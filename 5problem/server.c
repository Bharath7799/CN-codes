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

#define ssfifo "file1.dat"
#define shmkey 1234
#define shmsize 4

int ofd;

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
	struct pollfd fds[4];
	fds[0].fd=pfd[0];
	fds[1].fd=ffd;


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
	fds[2].fd=fileno(fp);

	fds[3].fd=0;
	printf("hii im before poll\n");
	int i;

	for (i = 0; i < 4; ++i)
	{
		fds[i].events=POLLIN;
	}

	printf("hii im after poll\n");

	int pid=fork();
	printf("pid : %d\n",pid );
	if(pid == 0)
	{  
		//char buf[128];
		// for(i=0; i<1000; i++)
		sleep(2);
		{
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
		printf("hii im in main process\n");
		int i=-1;
		while(1)
		{
			signal(SIGUSR1,handler);
		//	for (;;);
			
			int ret=poll(fds, 4 , 500);
			if(ret>0)
			{
				//printf("poll occured : ");
				sleep(1);
				for (i = 0; i < 4; ++i)
				{
					if(fds[i].revents & POLLIN )
					{

						printf("%d\n", i );
						char buf[128];
						memset(buf,128,'\0');
						int size=read(fds[i].fd,buf,128);
						if(size<0) printf("kuch bhiii\n");
						printf("%s\n",buf );
						mainsave(buf);

					}
				}
			}
		}
	}
	
	return 0;
}
