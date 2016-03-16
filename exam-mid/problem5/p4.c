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

#define shmkey 4567
#define shmsize 4

int init(int key)
{
	int shmid = shmget(key ,shmsize , IPC_CREAT|0666);
	if(shmid <=0)
	{
		printf("shmget error\n");
		exit(0);
	}
}

int main()
{
	int shmid= init(shmkey);
	int *ppid = (int *)shmat(shmid,NULL,0);
	int n;
	while(1)
	{
		scanf("%d",&n);
		if(n==1)
		kill(*ppid,SIGUSR1);
    }
}