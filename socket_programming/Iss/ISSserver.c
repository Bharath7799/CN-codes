#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main()
{
	fd_set readset;
	int maxfd;
	char buffer[100];
	
	struct in_addr st;
	st.s_addr=htonl(INADDR_ANY);
	
	int ports[4]={20000,20002,20004,20006};
	int fds[4]; int i;

	for (i = 0; i < 4; ++i)
	{
		fds[i]=socket(AF_INET,SOCK_STREAM ,0);
	}

	struct sockaddr_in myaddr;
	for (i = 0; i < 4; ++i)
	{
		myaddr.sin_family=AF_INET;
		myaddr.sin_port=htons(ports[i]);
		myaddr.sin_addr=st;

		if((bind(fds[i],(const struct sockaddr*)&myaddr,sizeof(myaddr)))>0)
		{
			printf("its good\n");
		}
		else
		{
			perror("bind error");
		}
		listen(fds[i],5);

	}
	

	struct sockaddr_in cliaddr;
	socklen_t clen;
	int j;
	
	while(1)
	{
		FD_ZERO(&readset);
	     for (j=0; j<4; j++)
	      {
	           FD_SET(fds[j], &readset);
	           maxfd = (maxfd>fds[j])?maxfd:fds[j];
	       }
		int ret=select(maxfd+1,&readset,NULL,NULL,NULL);
		if(ret>0)
		{
			for (i=0; i<4; i++)
		    { 
		       	if (FD_ISSET(fds[i], &readset))
		       	{	
		               int nsfd=accept(fds[i],(struct sockaddr*)&cliaddr,&clen);
		               if(fork()==0)
						{
							//close(fds[i]);
							int k;
							for (k = 0; k < 4; ++k)
							{
								close(fds[k]);
							}
							printf("i : %d \n",i);
							dup2(nsfd,0);
							//dup2(nsfd,1);
							close(nsfd);
							
							 char b[1024];
							 bzero(b,1024);
							recv(0,buffer,1024,0);
							strcpy(b,"./");
				        	strcat(b,buffer);
				        	strcat(b,"\0");
				        	write(1,b,sizeof(b));
				        	b[strlen(b)-1]='\0';

				        	FILE *fp;
							fp = popen(b, "r");
							if (fp == NULL)
							{
								printf("error in popen creation\n");
							}
							if(read(fileno(fp),buffer,1024)>0)
							{
								printf("%s\n",buffer );
								write(0,buffer,sizeof(buffer));
							}
							//execlp(b,b,(char *)0);
							//printf("exec error\n");
						}
							close(nsfd);
		        }
		    }
		 }
	}
}