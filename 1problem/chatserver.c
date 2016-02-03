#include <stdio.h>
#include <sys/types.h>
#include <poll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	//int f[4];
	int i=0;
	//while(i<4)
	//{
	//	mkfifo(argv[i+1],0666);
	//	f[i]=open(argv[i+1],O_RDWR);
    //i++;
	//}

  mkfifo("c1",0666);
  mkfifo("c2",0666);
  mkfifo("c3",0666);
  mkfifo("c4",0666);
  mkfifo("c11",0666);
  mkfifo("c22",0666);
  mkfifo("c33",0666);
  mkfifo("c44",0666);    

  int fd2[4];  


	  struct pollfd fdsf[4];
    int timeout_msecs = 500;
	  fdsf[0].fd = open("c1",O_RDWR|O_NONBLOCK);
    fdsf[0].events = POLLIN;
    fdsf[1].fd = open("c2",O_RDWR|O_NONBLOCK);
    fdsf[1].events = POLLIN;
    fdsf[2].fd = open("c3",O_RDWR|O_NONBLOCK);
    fdsf[2].events = POLLIN;
    fdsf[3].fd = open("c4",O_RDWR|O_NONBLOCK);
    fdsf[3].events = POLLIN;

    fd2[0]=open("c11",O_RDWR|O_NONBLOCK);
    fd2[1]=open("c22",O_RDWR|O_NONBLOCK);
    fd2[2]=open("c33",O_RDWR|O_NONBLOCK);
    fd2[3]=open("c44",O_RDWR|O_NONBLOCK);

    int j;

    while(1)
    {
    	int ret=poll(fdsf, 4, timeout_msecs);
    	if(ret>0)
    	{
        printf("messaged interrupted\n");
    		char buffer[1024];

    	for (i=0; i<4; i++)
     {
        
       		if (fdsf[i].revents & POLLIN)
      	 {
      	   		read(fdsf[i].fd,&buffer,1024);
              printf("%s\n",buffer);
      	   		for (j = 0; j < 4; j++)
      	   		{
      	   			if(j!=i)
      	   			{
      	   				write(fd2[j],&buffer,1024);
      	   			}
      	   		}
      	   		break;
        	}
        }
    	}
    }
}