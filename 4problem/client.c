#include <stdio.h>
#include <sys/types.h>
#include <poll.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define eerror(msg) { printf("%s\n", msg); exit(1); }
#define sfifo "fi.dat"


int main(int argc,char *argv[])
{
	 if(argc == 1)
         eerror("Usage: ./client <unique-name>");
     char buf[128], tmp[128];
    // mkfifo(sfifo,0666);
     
     
     strcpy(tmp, argv[1]);
     strcat(tmp, "r");
     mkfifo(tmp, 0666);
	
	strcpy(buf, argv[1]);
     strcat(buf, "w");
     mkfifo(buf, 0666);
     
     char str[128];
     strcpy(str,argv[1]);
     strcat(str," ");
     strcat(str,argv[2]);
     printf("%s\n", str );
    
    int fd = open(sfifo, 0666);
     write(fd, str , 128 );
      printf("sfifo opened in write mode\n");
    // close(fd);
     //printf("%s\n", tmp	); 		

      int fd_r = open(tmp, O_RDONLY);
     if(fd_r == -1) eerror("fd_r error");
     printf("open %s\n", tmp);


     int fd_w = open(buf, O_WRONLY);
     if(fd_w == -1) eerror("fd_w error");
     printf("open %s\n", buf);
     


     int pid;
     pid = fork();
     if(pid >0) { // parent process
         //close(fd_r);
         while(1){
             memset(tmp, 128, '\0');
             scanf("%s", tmp);
             write(fd_w, tmp, strlen(tmp)+1);
         }
     } else { // child process
         //close(fd_w);
         while(1){
             memset(buf, 128, '\0');
             read(fd_r, buf, 128);

             printf("%s\n", buf);
           //  sleep(2);
         }
     }
     return 0;
}