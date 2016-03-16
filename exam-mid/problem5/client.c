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
#define shmsize 4

#define shmkey5 8888
// #define handle_error(msg)  do { perror(msg); exit(EXIT_FAILURE); } while (0);
char ports[5][10]={"53000","53004","53008","53012","53016"};

int main()
{

	int nshmid4 = shmget(shmkey5 ,shmsize , IPC_CREAT|0666);
	int *count= (int *)shmat(nshmid4,NULL,0);

	char buffer[128];
	struct in_addr st;
	st.s_addr=htonl(INADDR_ANY);

	struct sockaddr_in serveraddr;
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(55000);
	serveraddr.sin_addr=st;

	int sfd=socket(AF_INET,SOCK_STREAM ,0);
	//connect(sfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

	 int cfd = connect(sfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
           if (cfd == -1)
               perror("connect");
printf("connection succesful\n");

//while(1)
	{
		while(1)
		{
			bzero(buffer,128);
			recv(sfd,buffer,128,0);
			if(strcmp(buffer,"echo")!=0)
			{
					printf("%s\n",buffer );
			}
			else
			{
				write(1,"going off",sizeof("going off"));
				break;
			}
		}
		sleep(3);
		bzero(buffer,128);
		int psfd;
		//recv(sfd,buffer,128,0);
		struct in_addr pst;
		pst.s_addr=htonl(INADDR_ANY);

		struct sockaddr_in pserveraddr;
		pserveraddr.sin_family=AF_INET;
		pserveraddr.sin_port=htons(atoi(ports[*count]));
		pserveraddr.sin_addr=pst;

		psfd=socket(AF_INET,SOCK_STREAM ,0);
		if(connect(psfd,(struct sockaddr*)&pserveraddr,sizeof(pserveraddr))>0)
		{
			printf("connection made with echoserver\n");
		}
		while(1)
		{
			bzero(buffer,128);
			recv(psfd,buffer,128,0);
			if(strcmp(buffer,"done")!=0)
			{
				write(1,buffer,128);
			}
			else
			{
				write(1,"going on",sizeof("going on"));
				break;
			}
		}
	}


}