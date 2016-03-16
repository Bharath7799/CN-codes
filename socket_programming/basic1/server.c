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

	struct sockaddr_in myaddr;
	myaddr.sin_family=AF_INET;
	myaddr.sin_port=htons(5100);
	myaddr.sin_addr=st;

	int sfd=socket(AF_INET,SOCK_STREAM ,0);
	bind(sfd,(const struct sockaddr*)&myaddr,sizeof(myaddr));
	listen(sfd,5);

	struct sockaddr_in cliaddr;
	socklen_t clen;
	int nsfd=accept(sfd,(struct sockaddr*)&cliaddr,&clen);

	while(1)
	{
		bzero(buffer,100);
		recv(nsfd,buffer,100,0);
		write(1,buffer,100);
		send(nsfd,buffer,strlen(buffer),0);
	}
	return 0;
}