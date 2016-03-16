#include <stdio.h>
#include <sys/types.h>
#include <poll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>


#define eerror(msg) { printf("%s\n", msg); exit(1); }
#define sfifo "c2s_fifo.dat"
#define MAX 10


//struct pollfd fdsf[MAX];
 int fd2[MAX],fd1[MAX]; int nClient=0,val;
char buffer[128], tmp[128];
      int j2;

void acceptReq(const char arg[])
{
     printf("Got a req %s\n",arg);
     strcpy(tmp, arg);
     strcat(tmp, "r");
     printf("%s\n",tmp );
     fd2[nClient] = open(tmp, O_WRONLY);
    // printf("%s%d\n",tmp,fd2[nClient] );
     if(fd2[nClient] == -1) eerror("WERROR!!!");
     
     strcpy(tmp, arg);
     strcat(tmp, "w");
     printf("%s\n",tmp );
      fd1[nClient]=open(tmp, O_RDONLY);
     if(fd1[nClient] == -1) eerror("RERROR!!!");
     nClient++;
     printf("Req success %d\n", nClient);
 }

int main()
{
     mkfifo(sfifo, 0666); int i,j;
     int fd = open(sfifo, O_RDONLY);
     if(fd == -1) eerror("sfifo error");
      fd_set readset;
      int maxfd;
       struct timeval tv;
       tv.tv_sec = 0;
       tv.tv_usec = 200;

    while(1)
    {
       FD_ZERO(&readset);
      FD_SET(fd,&readset);
      maxfd=fd;
     for (j=0; j<nClient; j++)
      {
           FD_SET(fd1[j], &readset);
           maxfd = (maxfd>fd1[j])?maxfd:fd1[j];
       }

    	int ret=select(maxfd+1,&readset,NULL,NULL,NULL);
      
    	if(ret>0)
    	{

        printf("messaged interrupted\n");
        if(FD_ISSET(fd,&readset))
        {
              memset(buffer,'\0',128);
              read(fd,buffer,128);
              printf("%s\n",buffer);
              FD_CLR(fd,&readset);
              acceptReq(buffer);
              close(fd);
              fd=open(sfifo,O_RDWR);
              if(fd>0)
              printf("opened again \n");
        }

    	for (i=0; i<nClient; i++)
     {
        
       		if (FD_ISSET(fd1[i], &readset))
      	 {
               memset(buffer,'\0',128);
      	   		 read(fd1[i],buffer,128);
               printf("%s\n",buffer);
      	   		  for (j = 0; j < nClient; j++)
      	   		  {
      	   			   if(j!=i)
      	   			   {
      	   				    write(fd2[j],&buffer,128);
      	   			   }
      	   		  }
                  break;
              }
        }
    	}
    }
}