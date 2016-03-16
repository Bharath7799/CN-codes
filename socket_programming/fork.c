#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main()
{
		int pid=fork();
		if(pid==0)
		{
		printf("\nim child");
		}
		else
		{
			printf("\nim parent");
		}
}

