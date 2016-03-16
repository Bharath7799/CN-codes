#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>


int main()
{
	struct in_addr st;
	st.s_addr=htonl(INADDR_ANY);

	char platports[3][10]={"21000","22000","23000"};
	
	int pfports=40000;
	int platforms[3];
	int fd;
	
		fd=socket(AF_INET,SOCK_STREAM ,0);

	struct sockaddr_in myaddr;

		myaddr.sin_family=AF_INET;
		myaddr.sin_port=htons(pfports);
		myaddr.sin_addr=st;

		if((bind(fd,(const struct sockaddr*)&myaddr,sizeof(myaddr)))>0)
		{
			printf("its good\n");
		}
		else
		{
			perror("bind error");
		}
		listen(fd,5);

	struct sockaddr_in cliaddr;
	socklen_t clen;


	int x=0; struct pollfd pds[3];

	while(x<3)
	{
		int nsfd=accept(fd,(struct sockaddr*)&cliaddr,&clen);
		platforms[x]=nsfd;
		pds[x].fd=nsfd;
		pds[x].events=POLLIN;
		x++;
	}



	struct in_addr tst;
	tst.s_addr=htonl(INADDR_ANY);
	
	int tports[3]={35000,35004,35008};
	int tfds[3]; int i;
	struct pollfd fds[3];

	for (i = 0; i < 3; ++i)
	{
		tfds[i]=socket(AF_INET,SOCK_STREAM ,0);
		fds[i].fd=tfds[i];
		fds[i].events=POLLIN;
	}

	printf("connection with platforms completed\n");
	struct sockaddr_in tmyaddr;
	for (i = 0; i < 3; ++i)
	{
		tmyaddr.sin_family=AF_INET;
		tmyaddr.sin_port=htons(tports[i]);
		tmyaddr.sin_addr=tst;

		if((bind(tfds[i],(const struct sockaddr*)&tmyaddr,sizeof(tmyaddr)))>0)
		{
			printf("its good\n");
		}
		else
		{
			perror("bind error");
		}
		listen(tfds[i],5);

	}
	

	struct sockaddr_in cliaddr2;
	socklen_t clen2;


	while(1)
	{
		printf("in while\n");
		if(poll(fds,3,500)>0)
		{
			for (i = 0; i < 3; ++i)
			{
				if (fds[i].revents && POLLIN)
				{
					int nsfd=accept(fds[i].fd,(struct sockaddr*)&cliaddr2,&clen2);
					printf("connection with train %d\n",i );
					int j;
					for (j = 0; j < 3; ++j)
					{
						char buffer[100]="train";
						send(platforms[j],buffer,sizeof(buffer),0);
						// bzero(buffer,100);
						// recv(fds[i].fd,buffer,100,0);
					}
					printf("message sent to all platforms\n");
					wait(5);
					int ret=poll(pds,3,500);
					if(ret>0)
					{ int k,flag=0;
						for (k = 0; k < 3; ++k)
						{
							if(flag==0)
							{
								if (pds[i].revents && POLLIN)
								{
									flag++;
									char tmp[100];
									recv(pds[i].fd,tmp,sizeof(tmp),0);
									printf("message received from platform  : %s\n",tmp);
									bzero(tmp,100);
									strcpy(tmp,platports[k]);
									send(nsfd,tmp,sizeof(tmp),0);
									send(pds[i].fd,tmp,sizeof(tmp),0);
								}
							}
						}
					}
				}
			}
		}
	}
}