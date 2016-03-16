#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
	char buffer[1024];
	struct in_addr st;
	st.s_addr=htonl(INADDR_ANY);

	struct sockaddr_in serveraddr;
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(atoi(argv[1]));
	serveraddr.sin_addr=st;

	int sfd=socket(AF_INET,SOCK_STREAM ,0);
	connect(sfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

	if(fork()==0)
	{
		while(1)
		{
			bzero(buffer,1024);
			recv(sfd,buffer,1024,0);
			write(1,buffer,sizeof(buffer));
		}
    }
    else
    {
    	while(1)
		{
			bzero(buffer,1024);
			read(0,buffer,1024);
			write(sfd,buffer,sizeof(buffer));
		}
    }

}