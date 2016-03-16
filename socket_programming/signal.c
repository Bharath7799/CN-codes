#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <poll.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void handler()
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

int main()
{
	//while(1)
	//{
	signal(SIGUSR1,handler);
		raise(SIGUSR1);
	//}
}