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
	myaddr.sin_port=htons(7778);
	myaddr.sin_addr=st;

	int sfd=socket(AF_INET,SOCK_STREAM ,0);
	if((bind(sfd,(const struct sockaddr*)&myaddr,sizeof(myaddr)))>0)
	{
		printf("its good\n");
	}
	else
	{
		perror("bind error");
	}
	listen(sfd,5);

	struct sockaddr_in cliaddr;
	socklen_t clen;
	

	while(1)
	{
		int nsfd=accept(sfd,(struct sockaddr*)&cliaddr,&clen);
		if(fork()==0)
		{
			close(sfd);
			dup2(nsfd,0);
			dup2(nsfd,1);
			close(nsfd);
			execlp("./s1","./s1",NULL);
		}
			close(nsfd);
	}
}