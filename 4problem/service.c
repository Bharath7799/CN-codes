#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <signal.h>

#define eerror(msg) { printf("%s\n", msg); exit(1); }
#define shmkey 1234
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
	char buf[30];
	printf("this is s1.c\n");
	//scanf("%s",buf);
	// execlp("ls", "ls", NULL);
	sleep(10);
		kill(*ppid,SIGUSR1);


	return 0;
}