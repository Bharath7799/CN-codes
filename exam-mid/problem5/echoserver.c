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

#define shmkey4 7777
#define shmkey5 8888



char ports[5][10]={"53000","53004","53008","53012","53016"};



int main(int argc,char *argv[])
{

	int nshmid4 = shmget(shmkey5 ,shmsize , IPC_CREAT|0666);
	int *count= (int *)shmat(nshmid4,NULL,0);

	int nshmid3 = shmget(shmkey4 ,15*sizeof(int) , IPC_CREAT|0666);
	int *values= (int *)shmat(nshmid3,NULL,0);

	char buffer[128];
	
	struct in_addr st;
	st.s_addr=htonl(INADDR_ANY);

	struct sockaddr_in myaddr;
	myaddr.sin_family=AF_INET;
	myaddr.sin_port=htons(atoi(ports[*count]));
	myaddr.sin_addr=st;

	int sfd=socket(AF_INET,SOCK_STREAM ,0);
	bind(sfd,(const struct sockaddr*)&myaddr,sizeof(myaddr));
	listen(sfd,5);

	struct sockaddr_in cliaddr;
	socklen_t clen;


	int nsfd=accept(sfd,(struct sockaddr*)&cliaddr,&clen);
	//int i=48;

	//while(i<50)
	//{
		//sleep(1);
		 bzero(buffer,128);
		 strcpy(buffer,"hiibrodas ");
		 send(nsfd,buffer,strlen(buffer),0);
		// i++;
		//}	

	bzero(buffer,128);
	strcpy(buffer,"done");
	send(nsfd,buffer,strlen(buffer),0);
	values[0]=0;
	return 0;
}