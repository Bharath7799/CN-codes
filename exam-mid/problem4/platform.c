#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int nTrains=0;
	char buffer[100];
	struct in_addr st;
	st.s_addr=htonl(INADDR_ANY);

	struct sockaddr_in serveraddr;
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(40000);
	serveraddr.sin_addr=st;

	int sfd=socket(AF_INET,SOCK_STREAM ,0);
	connect(sfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));


	while(1)
	{
		if(recv(sfd,buffer,100,0)>0)
		{
			if(nTrains==0)
			{
				send(sfd,"ready",sizeof("ready"),0);
				bzero(buffer,100);
				recv(sfd,buffer,100,0);
				int port=atoi(buffer);

				struct in_addr tst;
				tst.s_addr=htonl(INADDR_ANY);

				struct sockaddr_in tmyaddr;
				tmyaddr.sin_family=AF_INET;
				tmyaddr.sin_port=htons(port);
				tmyaddr.sin_addr=tst;

				int tsfd=socket(AF_INET,SOCK_STREAM ,0);
				bind(tsfd,(const struct sockaddr*)&tmyaddr,sizeof(tmyaddr));
				listen(tsfd,5);

				struct sockaddr_in tcliaddr;
				socklen_t tclen;
				int nsfd=accept(sfd,(struct sockaddr*)&tcliaddr,&tclen);
				printf("train connected succesfully\n");
				nTrains++;
				wait(15);
				printf("train went away\n");
				nTrains--;
			}
		}
	}
}