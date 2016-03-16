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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define ssfifo "file1.dat"
#define shmkey 4567
#define shmsize 4

#define shmkey2 5555
#define shmkey3 6666
#define shmkey4 7777
#define shmkey5 8888

int init(int key)
{
	int shmid = shmget(key ,shmsize , IPC_CREAT|0666);
	if(shmid <=0)
	{
		printf("shmget error\n");
		exit(0);
	}
}

	char ports[5][10]={"63000","63004","63008","63012","63016"};

void handler()
{

	int nshmid4 = shmget(shmkey5 ,shmsize , IPC_CREAT|0666);
	int *count= (int *)shmat(nshmid4,NULL,0);
	//*count=0;

	int nshmid2 = shmget(shmkey3 ,15*sizeof(int) , IPC_CREAT|0666);
	int *nsfd= (int *)shmat(nshmid2,NULL,0);

	int nshmid3 = shmget(shmkey4 ,15*sizeof(int) , IPC_CREAT|0666);
	int *values= (int *)shmat(nshmid3,NULL,0);

	printf("signal -- hii bro.\n");
	char buf[100];
		send(nsfd[*count],"echo",sizeof("echo"),0);
		strcpy(buf,"0");
		//sleep(1);
		//send(nsfd[*count],buf,sizeof(buf),0);

	if(fork()==0)
	{
		printf("hii im child of handler function\n");
		values[*count]=1;
		*count=*count+1;
		execl("./es","./es",buf,NULL);
	}
}


int main(int argc, char const *argv[])
{

	int shmid= init(shmkey);
	int *ppid = (int *)shmat(shmid,NULL,0);

	int nshmid = shmget(shmkey2 ,shmsize , IPC_CREAT|0666);
	int *nClient= (int *)shmat(nshmid,NULL,0);
	*nClient=0;

	int nshmid4 = shmget(shmkey5 ,shmsize , IPC_CREAT|0666);
	int *count= (int *)shmat(nshmid4,NULL,0);
	*count=0;

	int nshmid2 = shmget(shmkey3 , 15*sizeof(int) , IPC_CREAT|0666);
	int *nsfd= (int *)shmat(nshmid2,NULL,0);

	int nshmid3 = shmget(shmkey4 ,15*sizeof(int) , IPC_CREAT|0666);
	int *values= (int *)shmat(nshmid3,NULL,0);





	*ppid = getpid();
	int l;
	for (l = 0; l < 15; ++l)
	{
		nsfd[l]=0;
		values[l]=0;
	}

	struct pollfd fds[5];
	
	//pipe declaration;

	int pfd[2];
	pipe(pfd);

	//fifo declaration;

	int ffd;
	mkfifo("ssfifo",0666);
	ffd=open("ssfifo", O_RDWR);

	printf("pipe and fifo are created\n");

	fds[0].fd=pfd[0];
	fds[1].fd=ffd;

	//popen declaration

	FILE *fp;
	char path[128];
	fp = popen("./p3", "r");
	printf("popen started \n");
	fds[2].fd=fileno(fp);

	//standard input 
	fds[3].fd=0;

	printf("hii im before pollin\n");

	int i;

	for (i = 0; i < 4; ++i)
	{
		fds[i].events=POLLIN;
	}

	printf("hii im after pollin\n");

		int pid=fork();
		//printf("pid : %d\n",pid );
		if(pid == 0)
		{  
				char buf[128];
				printf("hii im child");
				sprintf(buf,"hii im child");
				write(pfd[1], buf, 128);
				close(pfd[1]);
		}
		if(pid > 0)
		{
			char buffer[128];
	
			struct in_addr st;
			st.s_addr=htonl(INADDR_ANY);

			struct sockaddr_in myaddr;
			myaddr.sin_family=AF_INET;
			myaddr.sin_port=htons(55000);
			myaddr.sin_addr=st;

			int sfd=socket(AF_INET,SOCK_STREAM ,0);
			bind(sfd,(const struct sockaddr*)&myaddr,sizeof(myaddr));
			listen(sfd,5);

			struct sockaddr_in cliaddr;
			socklen_t clen;
			fds[4].fd=sfd;

			printf("hii im in main process\n");
			int i=-1;
			while(1)
			{
				signal(SIGUSR1,handler);
				
				int ret=poll(fds, 5 , 500);
				if(ret>0)
				{
					for (i = 0; i < 5; ++i)
					{
						if(fds[i].revents & POLLIN )
						{
							if(i==4)
							{
								nsfd[*nClient]=accept(sfd,(struct sockaddr*)&cliaddr,&clen);
								*nClient=*nClient+1;
							}
							if(i!=4)
							{
								char buf[128];
								bzero(buf,128);
								int size=read(fds[i].fd,buf,128);
								if(size>0)
								{ 
									int k;
									for (k = 0; k < *nClient; ++k)
									{
										if(values[k]!=1)
										{
											printf("%s %d \n",buf,nsfd[k] );
											send(nsfd[k],buf,sizeof(buf),0);
										}
									}
								}
							}	
						}	
					}
				}
			}
		}
	return 0;
}
