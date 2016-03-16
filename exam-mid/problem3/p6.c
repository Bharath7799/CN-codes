#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main()
{
	while(1)
	{
	char buffer[1024];
	bzero(buffer,1024);
	read(0,buffer,1024);
	write(1,buffer,sizeof(buffer));
	}
}