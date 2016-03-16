#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main()
{
	char buffer[100];
	struct in_addr st;
	st.s_addr=htonl(INADDR_ANY);

	struct sockaddr_in serveraddr;
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(5100);
	serveraddr.sin_addr=st;

	int sfd=socket(AF_INET,SOCK_STREAM ,0);
	connect(sfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

	while(1)
	{
		bzero(buffer,100);
		read(0,buffer,100);

		send(sfd,buffer,strlen(buffer),0);
		recv(sfd,buffer,100,0);
		write(1,buffer,100);
	}

}