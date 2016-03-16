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

int main()
{
	char buffer[1024];
	int fds[4];
	FILE *fp[4];
	//int status;
	char path[128];
	fp[0] = popen("./p2", "r");
	printf("p2 started \n");
	fds[0]=fileno(fp[0]);

	fp[1] = popen("./p3", "r");
	printf("p3 started \n");
	fds[1]=fileno(fp[1]);

	fp[2] = popen("./p4", "r");
	printf("p4 started \n");
	fds[2]=fileno(fp[2]);

	fp[3] = popen("./p5", "r");
	printf("p5 started \n");
	fds[3]=fileno(fp[3]);


	FILE *f;
	f = popen("./p6", "w");
	printf("p6 started \n");
	int f6=fileno(f);

	struct pollfd fdsf[4];
	int i;
	for (i = 0; i < 4; ++i)
	{
		fdsf[i].fd = fds[i];
    	fdsf[i].events = POLLIN;
	}
	

     while(1)
    {
    	int ret=poll(fdsf, 4, 50);
    	if(ret>0)
    	{
    		int c=0;
    		//printf("poll occured %d \n",ret);
    		for (i=0; i<4; i++)
     		{
        
       			if (fdsf[i].revents & POLLIN)
      			{
      				bzero(buffer,1024);
               		if(read(fdsf[i].fd,buffer,1024)>0)
               		{
               		printf("poll occured %d\n",i);
               		write(f6,buffer,1024);
               		c++;
               	    }

       			}
        	}
        	if(c==0)
        	{
 
        		bzero(buffer,1024);
        			if(read(0,buffer,1024)>0)
    	 		write(f6,buffer,sizeof(buffer));
        	}

    	}
    	// else
    	// {
    	// 	printf("iam main process\n");
    	// 	bzero(buffer,1024);
    	// 	if(read(0,buffer,1024)>0)
    	// 		write(f6,buffer,1024);
    	// }
    }
}