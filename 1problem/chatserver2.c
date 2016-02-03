#include <stdio.h>
#include <sys/types.h>
#include <poll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define eerror(msg) { printf("%s\n", msg); exit(1); }
#define sfifo "c2s_fifo.dat"
#define MAX 10


struct pollfd fdsf[MAX];
 int fd2[MAX]; int nClient=1;
char buffer[128], tmp[128];

void acceptReq(const char arg[]){
     printf("Got a req %s\n",arg);
     strcpy(tmp, arg);
     strcat(tmp, "r");
     //mkfifo(tmp,0666);
     printf("%s\n",tmp );
     fd2[nClient] = open(tmp, O_WRONLY);
     if(fd2[nClient] == -1) eerror("WERROR!!!");
     
     strcpy(tmp, arg);
     strcat(tmp, "w");
     printf("%s\n",tmp );
    // mkfifo(tmp,0666);
     fdsf[nClient].fd = open(tmp, O_RDONLY);
     fdsf[nClient].events = POLLIN;
     if(fdsf[nClient].fd == -1) eerror("RERROR!!!");
     nClient++;
     printf("Req success %d\n", nClient);
 }

int main()
{
	//int i=0;
 // int fd;
   mkfifo(sfifo, 0666); int i,j;
   int timeout_msecs = 500;
     int fd = open(sfifo, O_RDONLY);
     if(fd == -1) eerror("sfifo error");
     fdsf[0].fd = fd;
     fdsf[0].events = POLLIN;

    while(1)
    {
    	int ret=poll(fdsf, nClient, timeout_msecs);
    	if(ret>0)
    	{
      //  printf("messaged interrupted\n");
    		//char buffer[128];

    	for (i=0; i<nClient; i++)
     {
        
       		if (fdsf[i].revents & POLLIN)
      	 {
               memset(buffer,'\0',128);
      	   		read(fdsf[i].fd,buffer,128);
              printf("%s\n",buffer);
              if(i==0)
              {
                char *str1;
                char *str2;
                str1=strtok(buffer," ");
                str2=strtok(NULL," ");
                printf("%s\n", str1 );
                printf("%s\n", str2 );
                  acceptReq(str1);
              }
              else
              {
      	   		  for (j = 1; j < nClient; j++)
      	   		  {
      	   			   if(j!=i)
      	   			   {
      	   				    write(fd2[j],&buffer,128);
      	   			   }
      	   		  }
              }
      	   		break;
        	}
        }
    	}
    }
}