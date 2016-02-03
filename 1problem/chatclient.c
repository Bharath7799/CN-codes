#include <stdio.h>
#include <sys/types.h>
#include <poll.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
	char *name = argv[1];
	printf("%s\n",name);
	//mkfifo(argv[1],0666);
	int fd1=open(argv[2],O_RDONLY|O_NONBLOCK);
	int fd2=open(argv[1],O_WRONLY|O_NONBLOCK);
	int fk;
	//int flag;

	struct pollfd fds;
    int timeout_msecs = 500;
	fds.fd = fd1;
    fds.events = POLLIN;
    char buff[200];
	fk=fork();
	if(fk==0)
	{
		while(1)
		{
			scanf("%s",buff);
			write(fd2,&buff,200);
		}
	}
	else
	{
		while(1)
		{
			int ret=poll(&fds, 1, timeout_msecs);
			if(ret>0)
			{
				char buffer[1024];
				read(fd1,&buffer,1024);
				printf("%s\n",buffer);
			}
		}
	}
}