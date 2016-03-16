#include<stdio.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/ipc.h>

int key1=555;
int key2=666;
int key3=777;
int key4=888;

void signals(int semid,int index)
{
	struct sembuf buff;
	buff.sem_num=index;
	buff.sem_op=1;
	buff.sem_flg=0;
	semop(semid,&buff,1);
}
void waits(int semid,int index)
{
	struct sembuf buff;
	buff.sem_num=index;
	buff.sem_op=-1;
	buff.sem_flg=0;
	semop(semid,&buff,1);
}

int x=2,y=2;
int *shm1,*shm2,*readbuff;

int main()
{
	int shmidx=shmget(key1,sizeof(int),IPC_CREAT|0666);
	int shmidy=shmget(key2,sizeof(int),IPC_CREAT|0666);
	int semidx=shmget(key3,sizeof(int),IPC_CREAT|0666);
	int semidy=shmget(key4,sizeof(int),IPC_CREAT|0666);

	semctl(semidx,0,SETVAL,0);
	semctl(semidy,0,SETVAL,0);

	shm1=(int *)shmat(shmidx,NULL,0);

	while(1)
	{
		*shm1=x;
		signals(semidx,0);
		waits(semidy,0);
		shm2=(int *)shmat(shmidy,NULL,0);
		int y=(int)*shm2;
		x=y+1;
	}


}




