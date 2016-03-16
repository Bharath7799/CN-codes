#include <stdio.h>
#include <sys/types.h>
#include <poll.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define eerror(msg) { printf("%s\n", msg); exit(1); }
#define sfifo "c2s_fifo.dat"

int fd_r,fd_w;
char buf[128], tmp[128];


void fun1()
{
         while(1){
             memset(tmp, 128, '\0');
             scanf("%s", tmp);
             write(fd_w, tmp, strlen(tmp)+1);
         }
}
void fun2()
{
    while(1){
             memset(buf, 128, '\0');
             read(fd_r, buf, 128);
             printf("%s\n", buf);
         }
}

int main(int argc,char *argv[])
{
    //pthread_t pread,pwrite;
	 if(argc == 1)
         eerror("Usage: ./client <unique-name>");

    // mkfifo(sfifo,0666);
     
     
     strcpy(tmp, argv[1]);
     strcat(tmp, "r");
     mkfifo(tmp, 0666);
	
	strcpy(buf, argv[1]);
     strcat(buf, "w");
     mkfifo(buf, 0666);
     
     char str[128];
     strcpy(str,argv[1]);
     // strcat(str," ");
     // strcat(str,argv[2]);
     // printf("%s\n", str );

    int fd = open(sfifo, O_WRONLY|O_NONBLOCK);
     write(fd, str , strlen(str));
     close(fd);

     fd_r = open(tmp, O_RDONLY);
     if(fd_r == -1) eerror("fd_r error");
     printf("%s%d\n",tmp,fd_r );
     printf("open %s\n", tmp);


     fd_w = open(buf, O_WRONLY);
     if(fd_w == -1) eerror("fd_w error");
     printf("open %s\n", buf);


    pthread_t A,B;
    pthread_create(&A, NULL, (void*)&fun1, NULL);
    pthread_create(&B, NULL, (void*)&fun2, NULL);
    pthread_join(A, NULL);
    pthread_join(B, NULL);

     return 0;
}