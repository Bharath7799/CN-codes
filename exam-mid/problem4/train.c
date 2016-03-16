#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
	char buffer[100];
	struct in_addr st;
	st.s_addr=htonl(INADDR_ANY);

	struct sockaddr_in serveraddr;
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(atoi(argv[1]));
	serveraddr.sin_addr=st;

	int sfd=socket(AF_INET,SOCK_STREAM ,0);
	connect(sfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

			bzero(buffer,100);
			
		if(recv(sfd,buffer,100,0)>0)
		{
			printf("message received\n");
			struct in_addr pst;
			pst.s_addr=htonl(INADDR_ANY);

			struct sockaddr_in pserveraddr;
			pserveraddr.sin_family=AF_INET;
			pserveraddr.sin_port=htons(atoi(buffer));
			pserveraddr.sin_addr=pst;

			int psfd=socket(AF_INET,SOCK_STREAM ,0);
			connect(psfd,(struct sockaddr*)&pserveraddr,sizeof(pserveraddr));
		}

		printf("bye bye \n");

}